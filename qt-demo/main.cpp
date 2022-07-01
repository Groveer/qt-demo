#include <test.h>

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    Test::Test test;
    qDebug() << test.add(1, 2);

    return a.exec();
}
