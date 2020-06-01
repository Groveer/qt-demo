#include "Demo/Property/MyClass.h"

#include <QApplication>
#include <QDebug>
#include <QScopedPointer>
#include <QSharedPointer>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QSharedPointer<MyClass> instance(new MyClass);
    QSharedPointer<QObject> obj(instance);

    instance->setPriority(MyClass::VeryHigh);
    obj->setProperty("priority", "VeryHigh");
    return a.exec();
}