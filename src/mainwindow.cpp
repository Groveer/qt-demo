#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QListView>
#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_list(new QListView)
{
    QVBoxLayout *layout(new QVBoxLayout);
    setLayout(layout);

    layout->addWidget(m_list);
    m_model = new CustomListModel();
    //添加测试数据库
    for(int i = 0; i < 5; i++)
    {
        CustomData data;
        data.Id = i + 1;
        data.Date = "today";
        data.Path = QString("This is %1").arg(QString::number(i+1));
        m_model->insertData(data);
    }
 
    m_delegate = new CustomDelegate();
 
    m_list->setModel(m_model);
    m_list->setItemDelegate(m_delegate);
    m_list->setMouseTracking(true);
 
}

void CustomListModel::insertData(CustomData data)
{
    m_listData.push_back(data);
}

void CustomListModel::removeData(int index) 
{
    if (m_listData.count() > index) {
        m_listData.removeAt(index);
    }
}
 
int CustomListModel::rowCount(const QModelIndex &parent) const
{
    return m_listData.size();
}
 
QVariant CustomListModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    int row = index.row();
 
    if(row>=m_listData.size()||(!index.isValid()))
    {
        return QVariant();
    }
 
    CustomData tmpData = m_listData.at(row);
 
    // 下面的role要和setData中的role一一对应；
    switch(role) {
    case Qt::UserRole+1:
        ret = tmpData.Id;
        break;
    case Qt::UserRole+2:
        ret = tmpData.Date;
        break;
    case Qt::UserRole+3:
        ret = tmpData.Path;
        break;
    default :
        break;
 
    }
    return ret;
}
 
bool CustomListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = false;
    int row = index.row();
 
    if(row>=m_listData.size()||(!index.isValid()))
    {
        return false;
    }
    CustomData tmpData = m_listData.at(row);
 
    switch(role) {
    case Qt::UserRole+1:
        tmpData.Id = value.toInt();
        ret = true;
        break;
    case Qt::UserRole+2:
        tmpData.Date = value.toString();
        ret = true;
        break;
    case Qt::UserRole+3:
        tmpData.Path = value.toString();
        ret =true;
        break;
    default :
        break;
    }
    m_listData.replace(row, tmpData);
    return ret;
}
 
void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect retc = option.rect;
 
    //这里取的数据 对应model里面的role
    // bool isSelect = index.data(Qt::UserRole+1).toBool();
    QString txt = index.data(Qt::UserRole+2).toString();
 
    //qDebug() << "paint data isSelect" << isSelect << "txt" << txt;
 
    QStyleOptionViewItem viewoption(option);
    initStyleOption(&viewoption, index);
    if(option.state.testFlag(QStyle::State_HasFocus))
    {
        viewoption.state = viewoption.state^QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, viewoption, index);
 
 
    //画按钮
    {
        QRect checboxRec(retc.right() - 30, retc.top() + (retc.height()-20)/2, 20, 20); //左边距10，竖直方向居中
 
        QPixmap pix(":/remove.png");
        painter->drawPixmap(checboxRec, pix);
    }
 
 
    //画txt
    {
        painter->save();
 
        //设置字体,颜色
        QFont font;
        font.setPixelSize(18);
        painter->setFont(font);
 
        // QRect txtRec(retc.left(), retc.top(), retc.width(), retc.height());
        painter->drawText(retc, Qt::AlignCenter, txt);
 
        painter->restore();
    }
}
 
bool CustomDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect retc = option.rect;
 
    //对应上面画的checkbox的retc
    QRect checboxRec(retc.right() - 30, retc.top() + (retc.height()-20)/2, 20, 20);
 
    //按钮点击事件；
    QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
    if(checboxRec.contains(mevent->pos()) && event->type() == QEvent::MouseButtonPress)
    {
        // bool value = model->data(index, Qt::UserRole+1).toBool();
        // model->setData(index, !value, Qt::UserRole+1);
        CustomListModel *tmpModel = dynamic_cast<CustomListModel *> (model);
        // qDebug() << index.row();
        // qDebug() << model->removeRow(index.row(), index);
        tmpModel->removeData(index.row());
        model->dataChanged(index, index);
 
        //此处可以添加自定义信号，即使checbox点击信号；
    }
 
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}