#include "domainmanager.h"

DomainManager::DomainManager()
{
    this->domains.insert("johannsson.co", QUrl("http://johannsson.co"));

    this->requestManager = new RequestManager();
}

DomainManager::~DomainManager()
{
    delete this->requestManager;
}
