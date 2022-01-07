#include "pluginmanager.h"
#include "pluginmanagerprivate.h"
#include "plugininterface.h"

#include <QDir>
#include <QCoreApplication>
#include <QLibrary>
#include <QPluginLoader>
#include <QDebug>

PluginManager* PluginManager::instance()
{
    // if (!m_instance)
    //     m_instance = new PluginManager();
    return new PluginManager();
}

PluginManager::PluginManager()
{
    d = new PluginManagerPrivate();
}

PluginManager::~PluginManager()
{

}

void PluginManager::loadAll()
{
    // 进入插件目录
    QDir path = QDir(qApp->applicationDirPath());
    path.cd("plugins");

    // 加载插件
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        load(info.absoluteFilePath());
}

void PluginManager::load(const QString& path)
{
    if (!QLibrary::isLibrary(path))
        return;

    // 获取元数据（名称、版本、依赖）
    QPluginLoader *loader = new QPluginLoader(path, this);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    if (loader->load()) {
        // 如果继承自 Plugin，则认为是自己的插件（防止外部插件注入）。
        PluginInterface *plugin = qobject_cast<PluginInterface *>(loader->instance());
        if (!plugin) {
            loader->deleteLater();
            qWarning() << path << " not own plugin!";
            return;
        }
    } else {
        return;
    }

    PluginData data(
        path,
        json.value("name").toVariant(),
        json.value("version").toVariant(),
        loader
    );
    d->Datas.append(data);

    loader->deleteLater();
}

void PluginManager::unloadAll()
{
    foreach (QPluginLoader* loader, plugins())
        unload(loader);
}

void PluginManager::unload(QPluginLoader* loader)
{
    // 卸载插件，并从内部数据结构中移除
    if (loader->unload()) {
        auto iter = std::find_if(d->Datas.constBegin(), d->Datas.constEnd(), [this, loader] (const PluginData& data) -> bool {
            if (data.Loader == loader)
                return true;
            else
                return false;
        });
        d->Datas.removeOne(*iter);
        loader->deleteLater();
    }
}

QList<QPluginLoader*> PluginManager::plugins()
{
    QList<QPluginLoader*> loaders;
    foreach (const PluginData& data, d->Datas) {
        loaders.append(data.Loader);
    }
    return loaders;
}
