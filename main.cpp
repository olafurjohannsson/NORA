
#include <QApplication>
#include <QtCore>
#include <QObject>
#include <QString>
#include <QLabel>
#include <QtNetwork/QTcpSocket>
#include <QIODevice>
#include <QByteArray>
#include <QMetaObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>

#include "mainwindow.h"
#include "requestmanager.h"


void recv(QString str)
{
    qDebug() << "recv.str" << str;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // create manager object
    auto *mgr = new RequestManager();

    //mgr->deleteLater();
    mgr->MakeHttpRequest("http://qt-project.org");


    // setup connection between http manager and window
    QObject::connect(mgr, SIGNAL(sendSignal(QString)), &w, SLOT(ReceiveString(QString)));



    return a.exec();
}





