#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QItemDelegate>
#include <QStyledItemDelegate>


/*
 * ReadOnly
 */
class ReadOnlyDelegate : public QItemDelegate{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = nullptr): QItemDelegate(parent) {}

    void setItems(QStringList items);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return NULL;
    }
};

/*
 * CheckBox
 */
class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CheckBoxDelegate(QObject *parent = nullptr);

    void setColumn(int col);

protected:
    void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
    bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);

private:
    int column;         //设置复选框的列
};

#endif // CHECKBOXDELEGATE_H
