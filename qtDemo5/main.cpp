#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch (const char *text) {
        QApplication a(argc, argv);
        QMessageBox::critical(nullptr, "exception", "exception throws", QMessageBox::Ok);
    }
    qDebug() << "endLine";
}
