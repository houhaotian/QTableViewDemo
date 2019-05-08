#include "MainWindow.h"
#include <QDebug>
#include <QTableView>
#include "TableModel.h"
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tableView = ui->tableView;
    TableModel *model = new TableModel;
    Delegate *delegate = new Delegate;

    m_tableView->setModel(model);

      m_tableView->setItemDelegate(delegate);
    m_tableView->setHorizontalHeader(new HeaderViewPrivate(Qt::Horizontal));
    connect(qobject_cast<HeaderViewPrivate *>(m_tableView->horizontalHeader()), &HeaderViewPrivate::checked, [&](bool ischecked) {
        if (ischecked) m_tableView->selectAll();
        else m_tableView->clearSelection();
    });
    QItemSelectionModel *selectionModel = m_tableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, model, &TableModel::onItemSelected);

    m_tableView->setSortingEnabled(true);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableView->horizontalHeader()->setSortIndicatorShown(true);
    m_tableView->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    m_tableView->horizontalHeader()->setSectionsClickable(true);
    connect(m_tableView->horizontalHeader(), &QHeaderView::sectionClicked, [](int index) {
        qDebug() << index;
    });
}
