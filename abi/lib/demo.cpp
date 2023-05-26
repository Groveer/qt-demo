#include "demo.h"

#include <QDebug>

#include <iostream>

namespace abi_demo {
Demo::Demo() { }

Demo::~Demo() { }

// void Demo::doSome(const QString &str)
// {
//     qDebug() << "doSome: " << str;
// }

void Demo::doSome(QString str, Arg size)
{
    qDebug() << "doSome: " << str;
}

QString Demo::some()
{
    return "some";
}

QString Demo::some1(QChar c)
{
    return QString(c);
}

} // namespace abi_demo
