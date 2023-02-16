#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTimer::singleShot(0, [] {
        qDebug() << "qt test!";
        qApp->quit();
    });
    return app.exec();
}
