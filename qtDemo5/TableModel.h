#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QPainter>
#include <QMouseEvent>
#include <QHeaderView>
#include <QCheckBox>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QAbstractTableModel *parent = 0);
    ~TableModel();

protected:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

public slots:
    void checkAll(Qt::CheckState);
    void onItemSelected(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QList<QStringList> m_stringList;
    QMap<int, Qt::CheckState> m_checkStatus;
};

class Delegate : public QItemDelegate
{
    Q_OBJECT

public: 
    Delegate(QItemDelegate *parent = 0);
    ~Delegate();

private:
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
     void setEditorData(QWidget *editor, const QModelIndex &index) const override;
     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const override;
};


class HeaderViewPrivate : public QHeaderView
{
    Q_OBJECT

public:
    explicit HeaderViewPrivate(Qt::Orientation orientation, QWidget * parent = 0)
        : QHeaderView(orientation, parent) {
        m_headerCbx = new QCheckBox(this);
        m_headerCbx->setVisible(true);
        connect(m_headerCbx, &QAbstractButton::clicked, this, &HeaderViewPrivate::checked);
    }

signals:
    void checked(bool);

protected:
    void updateGeometries() {
        m_headerCbx->move(sectionPosition(0) + 3, 6);
    }

private:
    QCheckBox *m_headerCbx;

};
