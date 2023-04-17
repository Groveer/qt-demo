#include <QApplication>
#include <QDebug>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLineEdit lineEdit;
    lineEdit.resize(200, 20);
    lineEdit.show();
    return app.exec();
}
