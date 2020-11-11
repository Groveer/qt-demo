#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QWidget>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

class QListView;
 
struct CustomData
{
    int Id;
    QString Date;
    QString Path;
};
 
class CustomListModel : public QAbstractListModel
{
    Q_OBJECT
 
public:
    void insertData(CustomData data);
    void removeData(int index);
 
    //必须实现的函数
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
 
private:
    QList<CustomData> m_listData;
};
 
 
class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
 
public:
    //描绘画面显示
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
 
    //处理鼠标事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};
 
class MainWindow : public QWidget
{
    Q_OBJECT
 
public:
    MainWindow(QWidget *parent = 0);
 
private:
    QListView *m_list;
    CustomListModel *m_model;
    CustomDelegate * m_delegate;
};
 
#endif // MAINWINDOW_H