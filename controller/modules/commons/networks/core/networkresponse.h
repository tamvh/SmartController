#ifndef NETWORKRESPONSE_H
#define NETWORKRESPONSE_H

#include <QNetworkReply>
#include "networkerror.h"

namespace Network {
namespace Core {

class NetworkRequest;
class NetworkErrorResponse;

class NetworkResponse
{
public:
    explicit NetworkResponse(NetworkRequest *request);
    virtual ~NetworkResponse();
public:
    void setReplyData(QNetworkReply *reply);
protected:
    /**
     * @brief parse network reply data
     * @param reply Network response
     * @return true if parseData ok
     */
    virtual bool parseData(QNetworkReply *reply) = 0;
    void reportError(NetworkError errorCategory, qint32 errorCode=0, const QString &errorMessage=QString());
protected:
    NetworkRequest *m_request;
};

}
}

#endif // NETWORKRESPONSE_H
