/*
 * Author:     guoyao <groveer@outlook.com>
 * Maintainer: guoyao <groveer@outlook.com>
 * Date:       2020/07/07
 * Description:the demo need global functions and variables
 */
#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDesktopWidget>

void setWindowCenter(QWidget *widget, QWidget *parent = nullptr)
{
    if (!parent) {
        parent = qApp->desktop();
    }

    const int &x((parent->width() - widget->width()) / 2);
    const int &y((parent->height() - widget->height()) / 2);
    widget->move(x, y);
}
#endif