#pragma once

#include <QObject>

class PluginInterface : public QObject
{
    Q_OBJECT
public:
    PluginInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~PluginInterface() {}
};

#define PluginInterface_iid "com.github.groveer.PluginInterface"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
