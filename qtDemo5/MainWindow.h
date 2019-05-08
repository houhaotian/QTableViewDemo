#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
  
private:
    Ui::MainWindow *ui;
    QObject *obj;
    QTableView *m_tableView;
};

