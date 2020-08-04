#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QApplication>
#include <QDebug>
#include <QStorageInfo>

void getFileSystem()
{
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("path", "storage path");
    parser.process(*qApp);

    const QString &path(parser.positionalArguments().first());
    QStorageInfo storageInfo(path);
    qDebug() << storageInfo.fileSystemType();
}

#endif