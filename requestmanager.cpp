#include "requestmanager.h"


///
/// RequestManager constructor
///
/// Description: sets up a network access manager that
///              abstract the HTTP/TCP protocol
RequestManager::RequestManager(QObject *parent) : QObject(parent)
{
    this->networkManager = new QNetworkAccessManager(this);
    this->networkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

    this->http_port = this->ssl_on ? 443 : 80;

    headers["User-Agent"] = "NORA 0.1 (Alpha)";
}

RequestManager::~RequestManager()
{
    //this->socket->close();
    qDebug() << "RequestManager dtor";
}

/// HTTP network request has finished
/// \brief RequestManager::handleFinished
/// \param networkReply
///
void RequestManager::handleFinished(QNetworkReply *networkReply)
{
    qDebug() << "handleFinished(QNetworkReply*)";

    // free later
    networkReply->deleteLater();

    // no error in request
    if (networkReply->error() == QNetworkReply::NoError)
    {
        qint32 http_status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        qDebug() << "code: " << http_status_code;

        if (http_status_code == 200)
        {
            QString reply = networkReply->readAll();
            qDebug() << "reply: " << reply;
        }
        else if (http_status_code == 301)
        {
            QUrl redirectUrl = networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

            // redirect url can be relative
            // we use previous url to resolve it
            redirectUrl = networkReply->url().resolved(redirectUrl);

            // redirect to new url
            QNetworkAccessManager *tempManager = networkReply->manager();
            QNetworkRequest redirection(redirectUrl);
            QNetworkReply *redirectReply = tempManager->get(redirection);

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
}

/// Error in HTTP request
/// \brief RequestManager::onError
/// \param code
///
void RequestManager::onError(QNetworkReply::NetworkError code)
{
    qDebug() << "onError: " << code;
}

QNetworkRequest RequestManager::constructNetworkRequest(const QString hostName, QMap<QString, QString> headers)
{
    QNetworkRequest request;
    request.setUrl(QUrl(hostName));

    // add headers if any
    if (!headers.isEmpty()) {
        QMapIterator<QString, QString> iterator(this->headers);
        while (iterator.hasNext()) {
            iterator.next();
            request.setRawHeader(QByteArray::fromStdString(iterator.key().toStdString()), QByteArray::fromStdString(iterator.value().toStdString()));
        }
    }

    return request;
}

QString RequestManager::POST(const QString hostName, QMap<QString, QString> data)
{
    if (this->networkManager == NULL)
        return NULL;

    connect(this->networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));

    QNetworkRequest request = this->constructNetworkRequest(hostName, this->headers);
    QByteArray postData;
    QMapIterator<QString, QString> iterator(data);
    while (true) {
        iterator.next();

        if (!iterator.hasNext()) {
            postData.append(iterator.key() + "=" + iterator.value());
            break;
        }
        else {
            postData.append(iterator.key() + "=" + iterator.value() + "&");
        }
    }


    this->networkManager->post(request, postData);

    return NULL;
}

/// Create a HTTP GET request and setup signals/slots
/// \brief RequestManager::MakeHttpRequest
/// \param hostName
/// \param data
/// \return
///
QString RequestManager::MakeHttpRequest(const QString hostName, const QString data)
{
    if (this->networkManager == NULL)
        return NULL;

    // step 1: setup finished signal
    connect(this->networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));

    // step 2: create http request with custom User-Agent header fixme: read from config
    QNetworkRequest request = this->constructNetworkRequest(hostName, this->headers);

    // step 3: send http request
    this->networkManager->get(request);

    return "success";
}

