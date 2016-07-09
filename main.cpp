
#include <QApplication>
#include <QtCore>
#include <QLabel>
#include <QString>
#include <QDebug>

#include "mainwindow.h"
#include "requestmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QLabel *site1 = w.findChild<QLabel*>("lblSite1");

    auto *mgr = new RequestManager();
    QString response = mgr->MakeHttpRequest("visir.is", "GET / \n\r");
    qDebug() << response;





    return a.exec();
}



