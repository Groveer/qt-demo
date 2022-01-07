#pragma once

#include <QObject>
#include <QString>
#include <QVariant>

class QPluginLoader;

struct PluginData
{
    PluginData() {}
    PluginData(const QString& path,
        const QVariant& name,
        const QVariant& version,
        QPluginLoader* loader) {
            Path = path;
            Name = name;
            Version = version;
            Loader = loader;
    }
    inline bool operator == (const PluginData& data) const {
        if (this->Path == data.Path)
            return true;
        else
            return false;
    }
    QString         Path;           //插件路径
    QVariant        Name;           //插件名称
    QVariant        Version;        //插件版本
    QPluginLoader*  Loader;         //插件实例
};


class PluginManagerPrivate
{
public:
    QList<PluginData> Datas;
};
