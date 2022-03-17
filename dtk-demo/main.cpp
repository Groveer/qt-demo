#include "utils/global.h"

#include <QApplication>
#include <QLabel>
#include <QDebug>

#include <DLineEdit>

DWIDGET_USE_NAMESPACE

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    DLineEdit edit;
    edit.setText("123");
    // QLabel label("This a test App!");
    // label.show();
    edit.show();
    edit.isAlert();
    Global::setWindowCenter(&edit);

    return a.exec();
}
