#include "sharedimage.h"

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;

    parser.setApplicationDescription("Shared memory server");
    parser.addHelpOption();

    QCommandLineOption shareOption({ { "s", "share" }, "eg: -s 1.jpg", "share image name" });
    parser.addOption(shareOption);
    parser.process(app);

    if (!parser.isSet(shareOption)) {
        parser.showHelp();
        return 1;
    }

    const auto &shareFile = parser.value(shareOption);
    if (!QFile::exists(shareFile)) {
        qWarning() << "File not found" << shareFile;
        return 1;
    }

    QScopedPointer<SharedImage> sharedImage(new SharedImage);
    sharedImage->wirteMemory(shareFile);

    return app.exec();
}
