#include <QObject>
#include <dtkcore_global.h>

DCORE_BEGIN_NAMESPACE
class DConfig;
DCORE_END_NAMESPACE

class Logger : public QObject {
  Q_OBJECT
public:
  explicit Logger(QObject *parent = nullptr);
  ~Logger();

  inline QString rules() const { return m_rules; }
  void setRules(const QString &rules);

private:
  void appendRules(const QString &rules);

private:
  QString m_rules;
  Dtk::Core::DConfig *m_config;
};
