/*
* Author:     guoyao <groveer@outlook.com>
* Maintainer: guoyao <groveer@outlook.com>
* Date:       2020/06/01
* Description:展示Qt的的属性用法
*/
#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>

class Property : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)
public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)
    Property(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

    void setPriority(Priority priority)
    {
        m_priority = priority;
        emit priorityChanged(priority);
    }
    Priority priority() const { return m_priority; }

signals:
    void priorityChanged(Priority priority);

private:
    Priority m_priority;
};

#endif