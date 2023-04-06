#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QTimer>

void messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr,
                "Debug: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr,
                "Info: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr,
                "Warning: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr,
                "Critical: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr,
                "Fatal: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        abort();
    }
}

Q_LOGGING_CATEGORY(dpm1, "demo.print.module1")
Q_LOGGING_CATEGORY(dpm2, "demo.print.module2")
Q_LOGGING_CATEGORY(dpm3, "demo.print.module3")
Q_LOGGING_CATEGORY(dpm4, "demo.print.module4")

int add(int a, int b)
{
    int c = a + b;
    qCInfo(dpm1) << "result:" << c;
    return c;
}

void print()
{
    // qDebug() << "hello world" << Q_FUNC_INFO;
    // qInfo("hello world");
    // qWarning("hello world");
    // qCritical("hello world");
    // qCDebug(dpm1) << "hello world";
    // qCInfo(dpm2) << "hello world";
    // qCWarning(dpm3) << "hello world";
    // qCCritical(dpm4) << "hello world";
    // qFatal("123");
    qCInfo(dpm2) << "add result:" << add(1, 2);
    qApp->quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    // qSetMessagePattern(
    //         "[%{time yyyy-MM-dd h:mm:ss.zzz t} %{file}:%{line} %{function} "
    //         "%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}"
    //         "C%{endif}%{if-fatal}F%{endif}] %{if-category}[ %{category} ]%{endif} %{message} ");
    // qInstallMessageHandler(messageOutput);
    qputenv("QT_LOGGING_RULES", "*.debug=false");
    QTimer::singleShot(0, print);
    return app.exec();
}
