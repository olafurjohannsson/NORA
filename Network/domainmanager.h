#include <QString>
#include <QUrl>
#include <QMap>
#include "requestmanager.h"

#ifndef DOMAINMANAGER_H
#define DOMAINMANAGER_H


class DomainManager
{
public:
    DomainManager();
    ~DomainManager();

private:
    QMap<QString, QUrl> domains;
    RequestManager *requestManager;
};

#endif // DOMAINMANAGER_H
