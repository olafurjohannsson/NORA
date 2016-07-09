#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QtCore>
#include <QObject>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QIODevice>
#include <QByteArray>
#include <QMetaObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>

class RequestManager : public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = 0);
    ~RequestManager() {}
    QString MakeHttpRequest(const QString hostName, const QString data);

signals:
    void sendSignal(QString data);

public slots:
    void handleFinished(QNetworkReply *networkReply);
    void handleFinished();
    void onError(QNetworkReply::NetworkError code);

    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QTcpSocket *socket;
    QNetworkReply *lastReply;
    qint32 http_port;
    bool ssl_on;
};

#endif // REQUESTMANAGER_H
