#include "requestmanager.h"


///
/// RequestManager constructor
///
/// Description: sets up a network access manager that
///              abstract the HTTP/TCP protocol
RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    // create network manager
    this->networkManager = new QNetworkAccessManager(this);
    this->networkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);


    // set HTTP headers
    headers["User-Agent"] = "NORA 0.1 (Alpha)";
}

RequestManager::~RequestManager()
{
    qDebug() << "RequestManager dtor";
    delete this->networkManager;
}

/// HTTP network request has finished
/// \brief RequestManager::handleFinished
/// \param networkReply
///
void RequestManager::handleFinished(QNetworkReply *networkReply)
{
    // free later
    networkReply->deleteLater();

    // no error in request
    if (networkReply->error() == QNetworkReply::NoError)
    {
        qint32 http_status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        qDebug() << "code: " << http_status_code;

        if (http_status_code == 200)
        {
            qDebug() << "sending signal";
            QString contentLength = networkReply->header(QNetworkRequest::KnownHeaders::ContentLengthHeader).toString();
            qDebug() << "contentLength: " << contentLength;
            this->sendSignal(networkReply->readAll());
        }
        else if (http_status_code == 301)
        {
            QUrl redirectUrl = networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

            // redirect url can be relative
            // we use previous url to resolve it
            redirectUrl = networkReply->url().resolved(redirectUrl);

            qDebug() << "redirectUrl: " << redirectUrl;

            // redirect to new url
            QNetworkAccessManager *tempManager = networkReply->manager();
            QNetworkRequest redirection(redirectUrl);
            tempManager->get(redirection);

            return;
        }
        else
        {
            qDebug() << "something else!";
        }
    }
    else
    {
        qDebug() << "errorString: " << networkReply->errorString();
    }

    networkReply->manager()->deleteLater();
}

/// Error in HTTP request
/// \brief RequestManager::onError
/// \param code
///
void RequestManager::onError(QNetworkReply::NetworkError code)
{
    qDebug() << "onError: " << code;
}

/// Create a HTTP GET request and setup signals/slots
/// \brief RequestManager::MakeHttpRequest
/// \param hostName
/// \param data
/// \return
///
void RequestManager::MakeHttpRequest(const QString hostName)
{
    if (this->networkManager == NULL)
        return;

    // step 1: setup finished signal
    connect(this->networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));

    // step 2: create http request with custom User-Agent header fixme: read from config
    QNetworkRequest request;
    request.setUrl(QUrl(hostName));

    // step 3: add custom headers
    QMapIterator<QString, QString> iterator(this->headers);
    while (iterator.hasNext()) {
        iterator.next();
        request.setRawHeader(QByteArray::fromStdString(iterator.key().toStdString()), QByteArray::fromStdString(iterator.value().toStdString()));
    }

    // step 4: send http request
    this->networkManager->get(request);
}
