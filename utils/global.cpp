#include "global.h"

#include <QApplication>
#include <QDesktopWidget>

namespace Global {
void setWindowCenter(QWidget *widget, QWidget *parent)
{
    if (!parent) {
        parent = qApp->desktop();
    }

    const int &x((parent->width() - widget->width()) / 2);
    const int &y((parent->height() - widget->height()) / 2);
    widget->move(x, y);
}

}
