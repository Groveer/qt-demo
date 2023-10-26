#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>

#include <dactiveconnection.h>
#include <dconnectionsetting.h>
#include <dipv4setting.h>
#include <dnetworkmanager.h>
#include <dsettingsmanager.h>

#include "qloggingcategory.h"

Q_LOGGING_CATEGORY(app_main, "org.deepin.test")

DNETWORKMANAGER_USE_NAMESPACE

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  DNetworkManager networkManager;

  QList<quint64> deviceList = networkManager.getDeviceIdList().value();
  qCDebug(app_main) << deviceList;
  auto primaryConnection = networkManager.primaryConnection();
  qCDebug(app_main) << primaryConnection;
  auto activeConn = networkManager.getActiveConnectionObject(primaryConnection);
  if (!activeConn) {
    qCDebug(app_main) << activeConn.error();
  }
  const auto &conn = activeConn.value();
  const auto &uuid = conn->UUID();

  DSettingsManager settingsManager;
  auto setting = settingsManager.getConnectionByUUID(uuid);

  if (!setting) {
    qCDebug(app_main) << setting.error();
  }

  DConnectionSetting connectionSetting(setting.value());

  qDebug() << connectionSetting.settings().value();

  // DIpv4Setting ipv4Setting;
  // ipv4Setting.fromMap(connectionSetting.settings().value()["ipv4"]);
  //
  // qDebug() << (int)ipv4Setting.method();

  // qCDebug(app_main) << active;
  // qCDebug(app_main) << active;
  // auto ipv4config_id = active->IP4Config();
  // DIPv4Config ipv4config = DIPv4Config(ipv4config_id);
  // qCDebug(app_main) << ipv4config.;

  app.exec();
}
