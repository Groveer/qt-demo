#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>

#include <dnetworkmanager.h>

#include "qloggingcategory.h"

Q_LOGGING_CATEGORY(app_main, "org.deepin.test")

DNETWORKMANAGER_USE_NAMESPACE

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  DNetworkManager networkManager;

  QList<quint64> deviceList = networkManager.getDeviceIdList().value();
  qCDebug(app_main) << deviceList;

  app.exec();
}
