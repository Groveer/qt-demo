#pragma once

#include <QObject>

class QPluginLoader;
class PluginManagerPrivate;

class PluginManager : public QObject
{
    Q_OBJECT

public:
    static PluginManager *instance();

    // 加载所有插件
    void loadAll();

    // 加载插件
    void load(const QString& path);

    // 卸载所有插件
    void unloadAll();

    // 卸载插件
    void unload(QPluginLoader* loader);

    // 获取所有插件
    QList<QPluginLoader *> plugins();

private:
    PluginManager();
    ~PluginManager();

private:
    static PluginManager *m_instance;
    PluginManagerPrivate *d;
};