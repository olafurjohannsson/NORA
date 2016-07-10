#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QtCore>
#include <QObject>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QIODevice>
#include <QByteArray>
#include <QMap>
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

    QString POST(const QString hostName, QMap<QString, QString> data);


signals:
    void sendSignal(QString data);

public slots:
    void handleFinished(QNetworkReply *networkReply);
    void onError(QNetworkReply::NetworkError code);

private:
    QNetworkRequest constructNetworkRequest(const QString hostName, QMap<QString, QString> headers);
    QNetworkAccessManager *networkManager;
    QMap<QString, QString> headers;
};

#endif // REQUESTMANAGER_H
