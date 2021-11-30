#pragma once

#include <QObject>

typedef struct xcb_image_t xcb_image_t;

class XImageManager : public QObject
{
    Q_OBJECT
public:
    XImageManager(QObject *parent = nullptr);
    ~XImageManager();

    QImage getImage(const int wid);

private:
    QSize calculateClientWindowSize(const int wid) const;
    bool isTransparentImage(const QImage &image) const;
    QImage convertFromNative(xcb_image_t *xcbImage) const;

};
