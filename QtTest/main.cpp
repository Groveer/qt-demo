#include "Demo/FindChild/FindChild.h"

#include <QApplication>
#include <QDebug>
#include <QScopedPointer>
#include <QSharedPointer>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    FindChild w;
    w.show();
    return a.exec();
}