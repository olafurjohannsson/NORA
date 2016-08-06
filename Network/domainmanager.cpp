#include "domainmanager.h"

DomainManager::DomainManager()
{
    this->domains.insert("johannsson.co", QUrl("http://johannsson.co"));
    this->domains.insert("johannsson.co", QUrl("http://olafurjohannsson.com"));
    this->domains.insert("johannsson.co", QUrl("http://faktura.is"));

    this->requestManager = new RequestManager();
    connect(this->domains, SIGNAL(RecvData()), this, SLOT(SendData()));
    for (auto domain, this->domains) {
        this->requestManager::GET(domain.value());
    }
}

DomainManager::RecvData()
{
    qDebug() << "recv";
}

DomainManager::~DomainManager()
{
    delete this->requestManager;
}
