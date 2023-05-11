#include <systemd/sd-journal.h>

#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include <QLoggingCategory>
#include <QTextStream>
#include <QThread>
#include <QTimer>

#include <iostream>

void stderr_message_handler(QtMsgType type,
                            const QMessageLogContext &context,
                            const QString &message)
{
    QString formattedMessage = qFormatLogMessage(type, context, message);

    // print nothing if message pattern didn't apply / was empty.
    // (still print empty lines, e.g. because message itself was empty)
    if (formattedMessage.isNull())
        return;

    fprintf(stderr, "%s\n", formattedMessage.toLocal8Bit().constData());
    fflush(stderr);
}

static QFile logFile("/tmp/log.txt");
static QTextStream logStream;

void file_message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    QString formattedMessage = qFormatLogMessage(type, context, message);

    // print nothing if message pattern didn't apply / was empty.
    // (still print empty lines, e.g. because message itself was empty)
    if (formattedMessage.isNull())
        return;
    if (logFile.isOpen())
        logStream << formattedMessage << endl;
}

void systemd_message_handler(QtMsgType type,
                             const QMessageLogContext &context,
                             const QString &message)
{

    QString formattedMessage = qFormatLogMessage(type, context, message);

    int priority = LOG_INFO; // Informational
    switch (type) {
    case QtDebugMsg:
        priority = LOG_DEBUG; // Debug-level messages
        break;
    case QtInfoMsg:
        priority = LOG_INFO; // Informational conditions
        break;
    case QtWarningMsg:
        priority = LOG_WARNING; // Warning conditions
        break;
    case QtCriticalMsg:
        priority = LOG_CRIT; // Critical conditions
        break;
    case QtFatalMsg:
        priority = LOG_ALERT; // Action must be taken immediately
        break;
    }

    sd_journal_send("MESSAGE=%s",
                    formattedMessage.toUtf8().constData(),
                    "PRIORITY=%i",
                    priority,
                    "CODE_FUNC=%s",
                    context.function ? context.function : "unknown",
                    "CODE_LINE=%d",
                    context.line,
                    "CODE_FILE=%s",
                    context.file ? context.file : "unknown",
                    "QT_CATEGORY=%s",
                    context.category ? context.category : "unknown",
                    "TID=%i",
                    QThread::currentThreadId(),
                    NULL);
}

void syslog_message_handler(QtMsgType type,
                            const QMessageLogContext &context,
                            const QString &message)
{
    QString formattedMessage = qFormatLogMessage(type, context, message);

    int priority = LOG_INFO; // Informational
    switch (type) {
    case QtDebugMsg:
        priority = LOG_DEBUG; // Debug-level messages
        break;
    case QtInfoMsg:
        priority = LOG_INFO; // Informational conditions
        break;
    case QtWarningMsg:
        priority = LOG_WARNING; // Warning conditions
        break;
    case QtCriticalMsg:
        priority = LOG_CRIT; // Critical conditions
        break;
    case QtFatalMsg:
        priority = LOG_ALERT; // Action must be taken immediately
        break;
    }

    syslog(priority, "%s", formattedMessage.toUtf8().constData());
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
    QElapsedTimer timer;
    timer.start();
    // qDebug() << "hello world" << Q_FUNC_INFO;
    // qInfo("hello world");
    // qWarning("hello world");
    // qCritical("hello world");
    // qCDebug(dpm1) << "hello world";
    // qCInfo(dpm2) << "hello world";
    // qCWarning(dpm3) << "hello world";
    // qCCritical(dpm4) << "hello world";
    // qFatal("123");
    // qDebug() << "add result:" << add(1, 2);
    for (int i = 0; i < 10; i++) {
        qCInfo(dpm1) << "hello world";
    }
    std::cout << "time:" << timer.elapsed() << std::endl;
    qApp->quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        logStream.setDevice(&logFile);
    }
    qSetMessagePattern(
            "[%{time yyyy-MM-dd h:mm:ss.zzz t} %{file}:%{line} %{function}] [pid: %{pid} tid: "
            "%{threadid}]"
            "[%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}"
            "C%{endif}%{if-fatal}F%{endif}] %{if-category}[ %{category} ]%{endif} %{message} ");
    qInstallMessageHandler(systemd_message_handler);
    qputenv("QT_LOGGING_RULES", "*.debug=false");
    QTimer::singleShot(0, print);
    QObject::connect(&app, &QCoreApplication::destroyed, &logFile, &QFile::close);
    return app.exec();
}
