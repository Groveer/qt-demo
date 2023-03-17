#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

void print()
{
    qDebug() << "holle world!";
    qApp->quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTimer::singleShot(0, print);
    return app.exec();
}
