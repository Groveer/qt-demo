#include "mainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void MainWindow::initUI()
{
    // setFocusPolicy(Qt::TabFocus);
    QVBoxLayout *mainLayout(new QVBoxLayout);
    QList<QPushButton*> btnList;
    for (int i = 1; i < 4; i++) {
        QPushButton *btn(new QPushButton);
        btn->setText(QString("btn%1").arg(i));
        mainLayout->addWidget(btn);
        btnList.append(btn);
    }
    setLayout(mainLayout);
    // btnList[0]->hide();
}
