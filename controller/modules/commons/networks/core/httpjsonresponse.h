#ifndef HTTPJSONRESPONSE_H
#define HTTPJSONRESPONSE_H

#include "networkresponse.h"
#include <QJsonValue>
#include <QJsonObject>

namespace Network {
namespace Core {

class HttpJsonResponse : public NetworkResponse
{
public:
    HttpJsonResponse(NetworkRequest *request);
protected:
    virtual bool parseData(QNetworkReply *reply);
    virtual bool parseData(QJsonValue &data);
protected:
    QJsonObject m_responseData;
};

}
}
#endif // HTTPJSONRESPONSE_H
