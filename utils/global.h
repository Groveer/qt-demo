/*
 * Author:     guoyao <groveer@outlook.com>
 * Maintainer: guoyao <groveer@outlook.com>
 * Date:       2020/07/07
 * Description:the demo need global functions and variables
 */
#pragma once

#include <QObject>
class QWidget;

namespace Global {

    void setWindowCenter(QWidget *widget, QWidget *parent = nullptr);
}