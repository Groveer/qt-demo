#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>
#include <QStorageInfo>

#include "Demo/FileSystem/FileSystem.h"


int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    getFileSystem();
    
    return 0;
}