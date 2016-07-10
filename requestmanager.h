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
    ~RequestManager();
    void MakeHttpRequest(const QString hostName);

signals:
    void sendSignal(QString data);

public slots:
    void handleFinished(QNetworkReply *networkReply);
    void onError(QNetworkReply::NetworkError code);

private:
    QNetworkAccessManager *networkManager;
    QMap<QString, QString> headers;
};

#endif // REQUESTMANAGER_H
