#include <QCoreApplication>
#include <QLocale>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    qDebug() << QLocale::system().name();
    return a.exec();
}
