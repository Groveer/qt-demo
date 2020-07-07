/*
 * Author:     guoyao <groveer@outlook.com>
 * Maintainer: guoyao <groveer@outlook.com>
 * Date:       2020/6/2
 * Description:Qt类父子关系
 */

#ifndef FINDCHILD_H
#define FINDCHILD_H

#include <QWidget>

class FindChild : public QWidget
{
private:
    /* data */
public:
    FindChild(QWidget *parent = nullptr);
    ~FindChild();
};

#endif