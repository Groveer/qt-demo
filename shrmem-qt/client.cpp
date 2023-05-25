#include "sharedimage.h"

#include <QApplication>
#include <QBuffer>
#include <QCommandLineParser>
#include <QDebug>
#include <QElapsedTimer>
#include <QImage>
#include <QLabel>
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();
    QApplication app(argc, argv);
    QCommandLineParser parser;

    parser.setApplicationDescription("Shared memory server");
    parser.addHelpOption();

    QCommandLineOption shareOption({ { "s", "share" }, "eg: -s 1.jpg", "share image name" });
    parser.addOption(shareOption);
    parser.process(app);

    const auto &shareFile = parser.value(shareOption);

    qDebug() << "time0:" << timer.elapsed() << "ms";
    QScopedPointer<SharedImage> sharedImage(new SharedImage);
    QScopedPointer<QLabel> label(new QLabel);
    if (shareFile.isEmpty()) {
        QScopedPointer<SharedImage> sharedImage(new SharedImage);
        void *data = nullptr;
        int size = 0;
        sharedImage->beginReadMemory(&data, size);
        qDebug() << "data" << data << "size:" << size;

        // QBuffer buff;
        // QDataStream in(&buff);
        // buff.setData((char *)data, size);
        // buff.open(QBuffer::ReadOnly);

        QImage pixmap;
        // in >> pixmap;
        qDebug() << "result:" << pixmap.loadFromData((uchar *)data, size, sharedImage->format());
        sharedImage->endReadMemory();
        label->setPixmap(QPixmap::fromImage(pixmap));
        qDebug() << "time share:" << timer.elapsed() << "ms";
    } else {
        QPixmap image(shareFile);
        label->setPixmap(image);
        qDebug() << "time file:" << timer.elapsed() << "ms";
    }
    label->show();
    qDebug() << "time:" << timer.elapsed() << "ms";
    return app.exec();
}
