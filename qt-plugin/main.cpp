#include "utils/global.h"

#include <QApplication>
#include <QLabel>
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QLabel label("This a test App!");
    label.show();
    Global::setWindowCenter(&label);

    return a.exec();
}
