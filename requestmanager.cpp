#include "requestmanager.h"


RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    this->socket = new QTcpSocket(this);
    this->networkManager = new QNetworkAccessManager(this);
    this->networkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    this->http_port = this->ssl_on ? 443 : 80;
}


void RequestManager::handleFinished(QNetworkReply *networkReply)
{
    //qDebug << QString(networkReply->readAll());
    qDebug() << "handleFinished(QNetworkReply*)";
}

void RequestManager::handleFinished()
{
    qDebug() << "handleFinished()";
    if (this->lastReply != NULL)
    {
        qDebug() << "this-lastReply != NULL";
        QByteArray buffer = this->lastReply->readAll();
        qDebug() << "buffer.length(): " << buffer.length();
        QString data = QString::fromUtf8(buffer.data());
        qDebug() << "data: " << data;
    }
}

void RequestManager::onError(QNetworkReply::NetworkError code)
{
    qDebug() << "onError: " << code;
}

void RequestManager::replyFinished(QNetworkReply *reply)
{
    qDebug() << "reply->readAll().length()" << reply->readAll().length();
}

QString RequestManager::MakeHttpRequest(const QString hostName, const QString data)
{
    if (this->socket == NULL)
        return NULL;

    // step 1: setup finished signal
    connect(this->networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleFinished(QNetworkReply*)));

    // step 2: create http request with a header
    QNetworkRequest request;
    request.setUrl(QUrl(hostName));
    request.setRawHeader("User-Agent", "NORA 0.1 (Alpha)");

    // step 3: send request and get reply
    QNetworkReply *reply = this->networkManager->get(request);
    this->lastReply = reply;

    // Connected
    //connect(reply, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleFinished()));

    QNetworkAccessManager mgr;

    connect(&mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));



    // Error
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onError(QNetworkReply::NetworkError)));

    return NULL;
}
