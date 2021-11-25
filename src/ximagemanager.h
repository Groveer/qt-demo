#pragma once

#include <QObject>

typedef struct _XImage XImage;
typedef struct _XDisplay Display;

class XImageManager : public QObject
{
    Q_OBJECT
public:
    XImageManager(QObject *parent = nullptr);
    ~XImageManager();

    bool getImageNormal(int wid, QImage &image);

private:
    XImage *getImageXlib(int wid);

private:
    Display *m_Display;
};
