#include "sharedimage.h"

#include <QBuffer>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QSharedMemory>

SharedImage::SharedImage(QObject *parent)
    : QObject(parent)
    , mShmWriter(new QSharedMemory("ImageShm", this))
    , mShmReader(new QSharedMemory("ImageShm", this))
{
}

char *SharedImage::format() const
{
    return (char *)"PPM";
}

void SharedImage::wirteMemory(const QString &imageFile)
{
    // 准备图片数据
    QImage image;
    if (!image.load(imageFile)) {
        qDebug() << "load image failed!";
        return;
    }
    QBuffer buff;
    buff.open(QBuffer::WriteOnly);
    image.save(&buff, format());

    if (mShmWriter->isAttached()) {
        // 还在连接状态则进行分离
        mShmWriter->detach();
    }
    qInfo() << "buff size:" << buff.size();
    // 创建共享内存
    if (!mShmWriter->create(buff.size()) && mShmWriter->error() == QSharedMemory::AlreadyExists) {
        mShmWriter->attach();
    } else {
        qDebug() << "create share memory failed!" << mShmWriter->errorString();
        return;
    }
    // 锁住共享区域
    mShmWriter->lock();
    // 拷贝数据到共享内存
    char *shmAddr = (char *)mShmWriter->data();
    const char *i_data = buff.data().data();
    memcpy(shmAddr, i_data, buff.size());
    // 解锁
    mShmWriter->unlock();
    buff.close();
}

void SharedImage::beginReadMemory(void **data, int &size)
{
    QPixmap image;
    // QImage image;
    // 锁定
    mShmReader->lock();
    // 关联共享内存
    if (!mShmReader->attach()) {
        qDebug() << "attach failed!" << mShmReader->errorString();
        return;
    }

    *data = mShmReader->data();
    size = mShmReader->size();
    // 解锁
    mShmReader->unlock();
}

void SharedImage::endReadMemory()
{
    mShmReader->detach();
}
