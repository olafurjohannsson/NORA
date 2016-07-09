

class RequestHandler : public QObject
{
    Q_OBJECT

public:
    explicit RequestHandler(QObject *parent = 0);

public slots:
    void onRequestCompleted();

private:
    QNetworkAccessManager *manager;
};

RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{
     manager = new QNetworkAccessManager(this);
}

void RequestHandler::onRequestCompleted()
{
    qDebug() << "onRequestCompleted";
}
