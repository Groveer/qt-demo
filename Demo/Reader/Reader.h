/*
* Author:     guoyao <groveer@outlook.com>
* Maintainer: guoyao <groveer@outlook.com>
* Date:       2020/07/07
* Description:用于创建一个自定义文件类型的默认程序
*/
#ifndef READER_H
#define READER_H

#include "../global.h"

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QLayout>
#include <QMimeDatabase>
#include <QUrl>
#include <QWidget>
#include <QDir>
#include <QRegularExpression>

#pragma region 检查是否
bool isMimeTypeSupport(const QString &filepath)
{
    const QString &mimeType = QMimeDatabase().mimeTypeForFile(filepath).name();
    qDebug() << "detect mime type: " << filepath << mimeType;
    if (mimeType == "text/txl")
        return true;
    return false;
}
#pragma endregion

#pragma region 
class UrlInfo
{
public:
    UrlInfo(QString path)
    {
        // Just check if the path is an existing file.
        if (QFile::exists(path)) {
            url = QUrl::fromLocalFile(QDir::current().absoluteFilePath(path));
            return;
        }

        const auto match = QRegularExpression(QStringLiteral(":(\\d+)(?::(\\d+))?:?$")).match(path);

        if (match.isValid()) {
            // cut away line/column specification from the path.
            path.chop(match.capturedLength());
        }

        // make relative paths absolute using the current working directory
        // prefer local file, if in doubt!
        url = QUrl::fromUserInput(path, QDir::currentPath(), QUrl::AssumeLocalFile);

        // in some cases, this will fail, e.g.
        // assume a local file and just convert it to an url.
        if (!url.isValid()) {
            // create absolute file path, we will e.g. pass this over dbus to other processes
            url = QUrl::fromLocalFile(QDir::current().absoluteFilePath(path));
        }
    }

    QUrl url;
};
#pragma endregion
void Reader(const QApplication &app)
{
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.process(app);

    QWidget *window(new QWidget);
    QVBoxLayout *layout(new QVBoxLayout);
    QLabel *label(new QLabel("This is a test window"));
    label->setWordWrap(true);

    layout->addWidget(label);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setLayout(layout);
    window->setMaximumWidth(800);
    window->adjustSize();
    setWindowCenter(window, app.desktop());
    window->show();

    if (!parser.positionalArguments().isEmpty()) {

        const UrlInfo &urlInfo(parser.positionalArguments().first());
        const QString &fileName(urlInfo.url.toLocalFile());
        if (!isMimeTypeSupport(fileName)) {
            qDebug() << QString("Invalid file: %1").arg(QFileInfo(fileName).fileName());
            return;
        }
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            label->setText(file.readAll());
        }
    }
}
#endif