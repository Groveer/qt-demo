#include "ximagemanager.h"

#include <QDebug>
#include <QImage>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

XImageManager::XImageManager(QObject *parent)
    : QObject(parent)
    , m_Display(XOpenDisplay(nullptr))
{

}

XImageManager::~XImageManager()
{
    XCloseDisplay(m_Display);
}

bool XImageManager::getImageNormal(int wid, QImage &image)
{
    qDebug() << "begin get image from win id:" << wid;
    _XImage* ximage = getImageXlib(wid);
    if (!ximage) {
        qDebug() << "get Image from Xlib failed! giving up...";
        return false;
    }
    QImage qimage = QImage((const uchar *)(ximage->data), ximage->width, ximage->height, ximage->bytes_per_line, QImage::Format_RGB32);
    image = qimage.copy();
    XDestroyImage(ximage);
    return true;
}

XImage* XImageManager::getImageXlib(int wid)
{
    if (!m_Display) {
        return nullptr;
    }

    Window unused_window;
    int unused_int;
    unsigned unused_uint, w, h;
    XGetGeometry(m_Display, wid, &unused_window, &unused_int, &unused_int, &w, &h, &unused_uint, &unused_uint);
    return XGetImage(m_Display, wid, 0, 0, w, h, AllPlanes, ZPixmap);
}
