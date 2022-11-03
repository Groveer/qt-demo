#ifndef DEMO_H
#define DEMO_H

#include <QSize>
#include <QObject>

namespace Example {
class Demo : public QObject
{
    Q_OBJECT
public:
    Demo(QObject *parent = nullptr);
    ~Demo();
    int add(const int a, const int b);

    // librsvg
    bool svg2png(const QString &svgfile, const QString &pngfile, QSize size = QSize(128, 128));
};
}  // namespace Example

#endif
