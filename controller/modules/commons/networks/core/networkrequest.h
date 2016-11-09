#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Network {
namespace Core {

class NetworkResponse;
class NetworkErrorResponse;

class NetworkRequest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkRequest(QObject *parent = 0);
    virtual ~NetworkRequest();
public:
    virtual NetworkResponse* responseObject() = 0;
    virtual QNetworkRequest* requestObject() = 0;
    virtual QNetworkReply* enqueue(QNetworkAccessManager *manager) = 0;
signals:
    void didReceiveResponse();
    void didReceiveError(NetworkErrorResponse *error);
};

}
}

#endif // NETWORKREQUEST_H
