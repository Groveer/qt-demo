#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "Demo/Reader/Reader.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    Reader(a);
    return a.exec();
}