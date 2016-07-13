#include "domainmanager.h"

DomainManager::DomainManager()
{
    this->domains.insert("johannsson.co", QUrl("http://johannsson.co"));
    this->domains.insert("johannsson.co", QUrl("http://olafurjohannsson.com"));
    this->domains.insert("johannsson.co", QUrl("http://faktura.is"));

    this->requestManager = new RequestManager();
}

DomainManager::~DomainManager()
{
    delete this->requestManager;
}
