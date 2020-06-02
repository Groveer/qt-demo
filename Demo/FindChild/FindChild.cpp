#include "FindChild.h"
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>

FindChild::FindChild(QWidget *parent)
    : QWidget(parent)
{
    // 构建部件
    QGroupBox *parentWidget = new QGroupBox(this);
    QGroupBox *subWidget = new QGroupBox(this);

    QCheckBox *pCheckBox1 = new QCheckBox(parentWidget);
    QCheckBox *pCheckBox2 = new QCheckBox(parentWidget);
    QCheckBox *pCheckBox3 = new QCheckBox(subWidget);
    QCheckBox *pCheckBox4 = new QCheckBox(subWidget);

    //设置标题
    parentWidget->setTitle("Parent");
    subWidget->setTitle("Child");

    // 设置文本
    pCheckBox1->setText("CheckBox1");
    pCheckBox2->setText("CheckBox2");
    pCheckBox3->setText("CheckBox3");
    pCheckBox4->setText("CheckBox4");

    // 设置objectName
    pCheckBox1->setObjectName("name");
    pCheckBox2->setObjectName("name1");
    pCheckBox3->setObjectName("name");
    pCheckBox4->setObjectName("name2");

    // 为subWidget设置布局，这时pCheckBox3、pCheckBox4均为它的孩子
    QVBoxLayout *pSubLayout = new QVBoxLayout();
    pSubLayout->addWidget(pCheckBox3);
    pSubLayout->addWidget(pCheckBox4);
    pSubLayout->setSpacing(10);
    pSubLayout->setContentsMargins(10, 10, 10, 10);
    subWidget->setLayout(pSubLayout);

    // 为parentWidget设置布局，这时pCheckBox1、pCheckBox2、以及subWidget均为它的孩子。
    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pCheckBox1);
    pLayout->addWidget(pCheckBox2);
    pLayout->addWidget(subWidget);
    pLayout->setSpacing(10);
    pLayout->setContentsMargins(10, 10, 10, 10);
    parentWidget->setLayout(pLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(parentWidget);
    setLayout(mainLayout);
}

FindChild::~FindChild() {}
