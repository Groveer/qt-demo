#include "global.h"

#include <QGuiApplication>
#include <QWidget>
#include <QScreen>

namespace Global {
void setWindowCenter(QWidget *widget, QWidget *parent)
{
    int x = 0;
    int y = 0;
    if (parent) {
        x = (parent->width() - widget->width()) / 2;
        y = (parent->height() - widget->height()) / 2;
    } else {
        auto &&desktopSize = qApp->primaryScreen()->availableSize();
        x = (desktopSize.width() - widget->width()) / 2;
        y = (desktopSize.height() - widget->height()) / 2;
    }

    widget->move(x, y);
}

}
