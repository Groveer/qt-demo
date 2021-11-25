#include "mainwindow.h"
#include "ximagemanager.h"

#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void MainWindow::initUI()
{
    QVBoxLayout *mainLayout(new QVBoxLayout(this));
    setLayout(mainLayout);

    QHBoxLayout *hLayout(new QHBoxLayout);
    QComboBox *cmb(new QComboBox(this));
    QPushButton *btn(new QPushButton("OK", this));
    btn->setMinimumWidth(40);
    btn->setDefault(true);
    cmb->setEditable(true);
    hLayout->addWidget(cmb);
    hLayout->addWidget(btn, -1);

    mainLayout->addLayout(hLayout, -1);
    QLabel *lblPixmap(new QLabel(this));
    mainLayout->addWidget(lblPixmap);


    connect(btn, &QPushButton::clicked, this, [=] {
        const QString &text = cmb->currentText().trimmed();
        if (text.isEmpty()) return;
        int winId = text.toInt();
        QImage image;
        XImageManager manager;
        if (manager.getImageNormal(winId, image)) {
            lblPixmap->clear();
            lblPixmap->setPixmap(QPixmap::fromImage(image));
        } else {
            return;
        }
        int i;
        for (i = 0; i < cmb->count(); i++) {
            if (text == cmb->itemText(i)) break;
        }
        if (i == cmb->count()) {
            cmb->addItem(text);
        }
    });
}
