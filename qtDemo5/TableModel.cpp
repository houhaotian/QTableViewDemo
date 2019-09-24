#include "TableModel.h"
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QSpinBox>

TableModel::TableModel(QAbstractTableModel *parent)
    : QAbstractTableModel(parent)
{
    for (int i = 0; i < 10; i++)
    {
        QStringList tempList;
        QList<Qt::CheckState> state;
        for (int j = 0; j < 3; j++) {
            tempList.append(QString("haha%1%2").arg(i).arg(j));
            state.append(Qt::Unchecked);
        }
        m_stringList.append(tempList);
    }  
}



TableModel::~TableModel()
{
}

QVariant TableModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return m_stringList.at(index.row()).at(index.column());
    case Qt::FontRole:
        return QFont("consolas", 9, 9);
    case Qt::TextAlignmentRole:
        if (index.column() == 0)
            return Qt::AlignCenter;
    case Qt::ForegroundRole:
        return QBrush(Qt::blue);
    case Qt::CheckStateRole:
        if (index.column() == 0)
            return m_checkStatus.value(index.row());
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
    return m_stringList.count();
}

int TableModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
    return m_stringList.at(0).count();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */) 
{
    if (index.isValid() && role == Qt::EditRole) {
        m_stringList[index.row()].replace(index.column(), value.toString());
        emit dataChanged(index, index, {role});
        return true;
    }
    else if (index.isValid() && role == Qt::CheckStateRole) {
        if(index.column() == 0)
            m_checkStatus.insert(index.row(), static_cast<Qt::CheckState>(value.toInt()));
        emit dataChanged(index, index, {role});
    }
    return QAbstractTableModel::setData(index, value, role);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0)
        return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;
    else
        return QAbstractItemModel::flags(index);
}

void TableModel::checkAll(Qt::CheckState state)
{
    for (int i = 0; i < rowCount(); ++i) {
        m_checkStatus.insert(i, state);
    }
}

void TableModel::onItemSelected(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList selectedModels = selected.indexes();
    QModelIndexList deselectedModels = deselected.indexes();

    foreach(auto &model, selectedModels) {
        m_checkStatus.insert(model.row(), Qt::Checked);
    }

    foreach(auto &model, deselectedModels) {
        m_checkStatus.insert(model.row(), Qt::Unchecked);
    }
}


Delegate::Delegate(QItemDelegate *parent /*= 0*/)
    : QItemDelegate(parent)
{
}

Delegate::~Delegate()
{
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(100);

    return editor;
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *e = qobject_cast<QSpinBox *>(editor);

    model->setData(index, QString("haha%1").arg(e->value()));
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *e = qobject_cast<QSpinBox *>(editor);
    QString value = index.model()->data(index, Qt::EditRole).toString();
    e->setValue(value.remove(0,4).toInt());
  
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}