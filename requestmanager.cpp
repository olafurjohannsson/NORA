#include "requestmanager.h"


RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    this->socket = new QTcpSocket(this);
    this->networkManager = new QNetworkAccessManager(this);
    this->http_port = this->ssl_on ? 443 : 80;
}


void RequestManager::slotReadyRead()
{
    qDebug() << "slotReadyRead";
}

void RequestManager::onRequestCompleted()
{
    qDebug() << "onRequestcompleted";
}

void RequestManager::onError(QNetworkReply::NetworkError code)
{
    qDebug() << "onError: " << code;
}

QString RequestManager::MakeHttpRequest(const QString hostName, const QString data)
{
    if (this->socket == NULL)
        return NULL;

    // step 1: setup request
    QNetworkRequest request;
    request.setUrl(QUrl(hostName));
    request.setRawHeader("User-Agent", "NORA 0.1 (Alpha)");

    // step 2: send request and get reply
    QNetworkReply *reply = this->networkManager->get(request);

    // Connected
    connect(reply, SIGNAL(finished()), SLOT(onRequestCompleted()));

    // Ready to read
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));

    // Error
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onError(QNetworkReply::NetworkError)));

    return NULL;
}
