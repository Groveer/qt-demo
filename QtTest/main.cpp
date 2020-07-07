#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QLayout>
#include <QMimeDatabase>
#include <QScopedPointer>
#include <QUrl>
#include <QWidget>

void setWindowCenter(QWidget *widget, QWidget *parent = nullptr)
{
    const int &x((parent->width() - widget->width()) / 2);
    const int &y((parent->height() - widget->height()) / 2);
    widget->move(x, y);
}

bool isMimeTypeSupport(const QString &filepath)
{
    const QString &mimeType = QMimeDatabase().mimeTypeForFile(filepath).name();
    qDebug() << "detect mime type: " << filepath << mimeType;
    if (mimeType == "text/txl")
        return true;
    return false;
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.process(a);

    QScopedPointer<QWidget> window(new QWidget);
    QVBoxLayout *layout(new QVBoxLayout);
    QLabel *label(new QLabel("This is a test window"));
    label->setWordWrap(true);

    layout->addWidget(label);
    window->setLayout(layout);
    window->setMaximumWidth(800);
    window->adjustSize();
    setWindowCenter(window.data(), a.desktop());
    window->show();

    if (!parser.positionalArguments().isEmpty()) {
        const QUrl &url(parser.positionalArguments().first());
        const QString &fileName(url.toLocalFile());
        if (!isMimeTypeSupport(fileName)) {
            qDebug() << QString("Invalid file: %1").arg(QFileInfo(fileName).fileName());
            return 1;
        }
        QFile file(url.toLocalFile());

        if (file.open(QIODevice::ReadOnly)) {
            label->setText(file.readAll());
        }
    }
    return a.exec();
}