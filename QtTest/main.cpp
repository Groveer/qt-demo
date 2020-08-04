#include <QApplication>
#include <QDebug>
#include <QString>


int main(int argc, char **argv)
{
    QApplication a(argc, argv);

#ifdef MKGRUB
    qDebug() << "current processor is mips64";
#else
    qDebug() << "current processor is not mips64";
#endif
    return 0;
}