#include "ximagemanager.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QX11Info>

#include <xcb/xcb_atom.h>
#include <xcb/xcb_event.h>
#include <xcb/xcb_image.h>

void sni_cleanup_xcb_image(void *data)
{
    xcb_image_destroy(static_cast<xcb_image_t *>(data));
}

XImageManager::XImageManager(QObject *parent)
    : QObject(parent)
{

}

XImageManager::~XImageManager()
{

}

QImage XImageManager::getImage(const int wid)
{
    auto c = QX11Info::connection();

    QSize clientWindowSize = calculateClientWindowSize(wid);

    xcb_image_t *image = xcb_image_get(c, wid, 0, 0, clientWindowSize.width(), clientWindowSize.height(), 0xFFFFFFFF, XCB_IMAGE_FORMAT_Z_PIXMAP);

    // Don't hook up cleanup yet, we may use a different QImage after all
    QImage naiveConversion;
    if (image) {
        naiveConversion = QImage(image->data, image->width, image->height, QImage::Format_ARGB32);
    } else {
        qDebug() << "Skip NULL image returned from xcb_image_get() for" << wid;
        return QImage();
    }

    if (isTransparentImage(naiveConversion)) {
        QImage elaborateConversion = QImage(convertFromNative(image));

        // Update icon only if it is at least partially opaque.
        // This is just a workaround for X11 bug: xembed icon may suddenly
        // become transparent for a one or few frames. Reproducible at least
        // with WINE applications.
        if (isTransparentImage(elaborateConversion)) {
            qDebug() << "Skip transparent xembed icon for" << wid;
            return QImage();
        } else
            return elaborateConversion;
    } else {
        // Now we are sure we can eventually delete the xcb_image_t with this version
        return QImage(image->data, image->width, image->height, image->stride, QImage::Format_ARGB32, sni_cleanup_xcb_image, image);
    }
}

bool XImageManager::isTransparentImage(const QImage &image) const
{
    int w = image.width();
    int h = image.height();

    // check for the center and sub-center pixels first and avoid full image scan
    if (!(qAlpha(image.pixel(w >> 1, h >> 1)) + qAlpha(image.pixel(w >> 2, h >> 2)) == 0))
        return false;

    // skip scan altogether if sub-center pixel found to be opaque
    // and break out from the outer loop too on full scan
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            if (qAlpha(image.pixel(x, y))) {
                // Found an opaque pixel.
                return false;
            }
        }
    }

    return true;
}

QImage XImageManager::convertFromNative(xcb_image_t *xcbImage) const
{
    QImage::Format format = QImage::Format_Invalid;

    switch (xcbImage->depth) {
    case 1:
        format = QImage::Format_MonoLSB;
        break;
    case 16:
        format = QImage::Format_RGB16;
        break;
    case 24:
        format = QImage::Format_RGB32;
        break;
    case 30: {
        // Qt doesn't have a matching image format. We need to convert manually
        quint32 *pixels = reinterpret_cast<quint32 *>(xcbImage->data);
        for (uint i = 0; i < (xcbImage->size / 4); i++) {
            int r = (pixels[i] >> 22) & 0xff;
            int g = (pixels[i] >> 12) & 0xff;
            int b = (pixels[i] >> 2) & 0xff;

            pixels[i] = qRgba(r, g, b, 0xff);
        }
        // fall through, Qt format is still Format_ARGB32_Premultiplied
        Q_FALLTHROUGH();
    }
    case 32:
        format = QImage::Format_ARGB32_Premultiplied;
        break;
    default:
        return QImage(); // we don't know
    }

    QImage image(xcbImage->data, xcbImage->width, xcbImage->height, xcbImage->stride, format, sni_cleanup_xcb_image, xcbImage);

    if (image.isNull()) {
        return QImage();
    }

    if (format == QImage::Format_RGB32 && xcbImage->bpp == 32) {
        QImage m = image.createHeuristicMask();
        QBitmap mask(QPixmap::fromImage(m));
        QPixmap p = QPixmap::fromImage(image);
        p.setMask(mask);
        image = p.toImage();
    }

    // work around an abort in QImage::color
    if (image.format() == QImage::Format_MonoLSB) {
        image.setColorCount(2);
        image.setColor(0, QColor(Qt::white).rgb());
        image.setColor(1, QColor(Qt::black).rgb());
    }

    return image;
}

QSize XImageManager::calculateClientWindowSize(const int wid) const
{
    auto c = QX11Info::connection();

    auto cookie = xcb_get_geometry(c, wid);
    QScopedPointer<xcb_get_geometry_reply_t, QScopedPointerPodDeleter> clientGeom(xcb_get_geometry_reply(c, cookie, nullptr));

    QSize clientWindowSize;
    if (clientGeom) {
        clientWindowSize = QSize(clientGeom->width, clientGeom->height);
    }

    return clientWindowSize;
}

