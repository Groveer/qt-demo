#include <QCoreApplication>
#include <QtConcurrent>

#include <DLog>

#include "dtkcore_global.h"
#include "logger.h"
#include "qloggingcategory.h"

Q_LOGGING_CATEGORY(dpm1, "org.deepin.test.module1")
Q_LOGGING_CATEGORY(dpm2, "org.deepin.test.module2")
Q_LOGGING_CATEGORY(dpm3, "org.deepin.test.module3")
Q_LOGGING_CATEGORY(dpm4, "org.deepin.test.module4")

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);
  qputenv("QT_LOGGING_RULES", "*.debug=false;*.info=false");

  // 为了兼容性
#if (DTK_VERSION >= DTK_VERSION_CHECK(5, 6, 8, 0))
  Dtk::Core::DLogManager::registerJournalAppender();
#else
  Dtk::Core::DLogManager::registerFileAppender();
#endif
#ifdef QT_DEBUG
  Dtk::Core::DLogManager::registerConsoleAppender();
#endif

  Logger logger;
  QtConcurrent::run([] {
    while (true) {
      qCDebug(dpm1) << "debug test1";
      qCInfo(dpm2) << "info test2";
      qCWarning(dpm3) << "warning test3";
      qCCritical(dpm4) << "critical test4";
      QThread::sleep(3);
    }
  });
  app.exec();
}
