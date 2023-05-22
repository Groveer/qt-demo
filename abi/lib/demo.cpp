#include "demo.h"

#include <QDebug>

#include <iostream>

namespace abi_demo {
Demo::Demo() { }

Demo::~Demo() { }

void Demo::doSome(const QString &str)
{
    qDebug() << "doSome: " << str;
}
} // namespace abi_demo
