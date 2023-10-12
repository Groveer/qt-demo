#include "logger.h"
#include "dtkcore_global.h"
#include "qglobal.h"

#include <QLoggingCategory>
#include <QObject>

#include <DConfig>

DCORE_USE_NAMESPACE

Logger::Logger(QObject *parent)
    : QObject(parent), m_rules(""), m_config(nullptr) {
  QByteArray logRules = qgetenv("QT_LOGGING_RULES");
  qunsetenv("QT_LOGGING_RULES");

  // set env
  m_rules = logRules;

  // set dconfig
  m_config = DConfig::create("org.deepin.test", "org.deepin.test");
  logRules = m_config->value("log_rules").toByteArray();
  appendRules(logRules);
  setRules(m_rules);

  // watch dconfig
  connect(m_config, &DConfig::valueChanged, this, [this](const QString &key) {
    if (key == "log_rules") {
      qDebug() << "value changed:" << key;
      setRules(m_config->value(key).toByteArray());
    }
  });
}

Logger::~Logger() { m_config->deleteLater(); }

void Logger::setRules(const QString &rules) {
  auto tmpRules = rules;
  m_rules = tmpRules.replace(";", "\n");
  QLoggingCategory::setFilterRules(m_rules);
}

void Logger::appendRules(const QString &rules) {
  QString tmpRules = rules;
  tmpRules = tmpRules.replace(";", "\n");
  auto tmplist = tmpRules.split('\n');
  for (int i = 0; i < tmplist.count(); i++)
    if (m_rules.contains(tmplist.at(i))) {
      tmplist.removeAt(i);
      i--;
    }
  if (tmplist.isEmpty())
    return;
  m_rules.isEmpty() ? m_rules = tmplist.join("\n")
                    : m_rules += "\n" + tmplist.join("\n");
}
