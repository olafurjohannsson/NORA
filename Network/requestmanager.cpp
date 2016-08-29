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
    connect(this->networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));

    // set HTTP headers
    headers["User-Agent"] = "NORA 0.1 (Alpha)";
}

/// Destructor
/// \brief RequestManager::~RequestManager
///
RequestManager::~RequestManager()
{
    qDebug() << "RequestManager dtor";
    delete this->networkManager;
}

///
/// \brief RequestManager::HEAD
/// \param hostName
///
void RequestManager::HEAD(const QString hostName)
{
    // step 1: create http request with custom headers
    QNetworkRequest request = this->constructNetworkRequest(hostName, this->headers);

    // step 2: HEAD to this resource
    this->networkManager->head(request);
}

///
/// \brief RequestManager::PUT
/// \param hostName
///
void RequestManager::PUT(const QString hostName, QMap<QString, QString> data)
{
    // step 1: create http request with custom headers
    QNetworkRequest request = this->constructNetworkRequest(hostName, this->headers);

    // step 2: get PUT data
    QUrlQuery putData = this->constructPostData(data);

    // step 3: PUT to this resource
    this->networkManager->put(request, putData.toString(QUrl::FullyEncoded).toUtf8());
}

/// Create a HTTP POST request and setup signals/slots
/// \brief RequestManager::POST
/// \param hostName
/// \param data
///
void RequestManager::POST(const QString hostName, QMap<QString, QString> data)
{
    // step 1: create http request with custom headers
    QNetworkRequest request = this->constructNetworkRequest(hostName, this->headers);

    // step 2: get POST data
    QUrlQuery postData = this->constructPostData(data);

    // step 3: POST to this resource
    this->networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

/// Create a HTTP GET request and setup signals/slots
/// \brief RequestManager::GET
/// \param hostName
///
void RequestManager::GET(const QString hostName)
{
    // step 1: create http request with custom User-Agent headers
    QNetworkRequest request = this->constructNetworkRequest(hostName, this->headers);

    // step 2: send http request
    QNetworkReply *reply = this->networkManager->get(request);
    //reply->deleteLater();
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void RequestManager::readyRead()
{
    qDebug() << "readyRead()";
}

/*
 *
 * SIGNALS/SLOTS
 *
 */
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
        // get HTTP status code
        qint32 httpStatusCode = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        // 200
        if (httpStatusCode >= 200 && httpStatusCode < 300) // OK
        {
            qDebug() << "sending signal";
            this->sendSignal(networkReply->readAll());
        }
        else if (httpStatusCode >= 300 && httpStatusCode < 400) // 300 Redirect
        {
            // Get new url, can be relative
            QUrl relativeUrl = networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

            // url can be relative, we use the previous url to resolve it
            QUrl redirectUrl = networkReply->url().resolved(relativeUrl);

            // redirect to new url
            networkReply->manager()->get(QNetworkRequest(redirectUrl));

            // maintain manager
            return;
        }
        else if (httpStatusCode >= 400 && httpStatusCode < 500) // 400 Error
        {
            qDebug() << httpStatusCode << " Error!";
        }
        else if (httpStatusCode >= 500 && httpStatusCode < 600) // 500 Internal Server Error
        {
            qDebug() << httpStatusCode << " Error!";
        }
        else
        {
            qDebug() << "Status code invalid! " << httpStatusCode;
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

/*
 *
 *  HELPERS
 *
 */

/// Create correct POST data
/// \brief RequestManager::constructPostData
/// \param data
/// \return
///
QUrlQuery RequestManager::constructPostData(QMap<QString, QString> data)
{
    // Create POST/PUT data
    QUrlQuery postData;
    QMapIterator<QString, QString> iterator(data);

    // add all keys from map
    while (iterator.hasNext()) {
        iterator.next();
        postData.addQueryItem(iterator.key(), iterator.value());
    }
    return postData;
}

/// Create network request
/// \brief RequestManager::constructNetworkRequest
/// \param hostName
/// \param headers
/// \return
///
QNetworkRequest RequestManager::constructNetworkRequest(const QString hostName, QMap<QString, QString> headers)
{
    // create HTTP request and set hostname
    QNetworkRequest request;
    request.setUrl(QUrl(hostName));

    // setup error handling
    //QObject::connect(&request, SIGNAL(onError(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

    // add headers
    /*
    if (!headers.isEmpty()) {
        QMapIterator<QString, QString> iterator(headers);
        while (iterator.hasNext()) {
            iterator.next();
            request.setRawHeader(QByteArray::fromStdString(iterator.key().toStdString()), QByteArray::fromStdString(iterator.value().toStdString()));
        }
    }
*/
    return request;
}
