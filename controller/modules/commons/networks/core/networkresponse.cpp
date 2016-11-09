#include "networkresponse.h"
#include "networkrequest.h"
#include "networkerrorresponse.h"

namespace Network {
namespace Core {

NetworkResponse::NetworkResponse(NetworkRequest *request):
    m_request(request)
{
}

NetworkResponse::~NetworkResponse()
{

}

void NetworkResponse::setReplyData(QNetworkReply *reply)
{
    if (reply->error()) {
        reportError(NetworkErrorConnection, reply->error(), reply->errorString());
    } else {
        bool canParse = parseData(reply);
        if (canParse) {
            emit m_request->didReceiveResponse();
        } else {
            reportError(NetworkErrorInvalidResponse);
        }
    }
}

void NetworkResponse::reportError(NetworkError errorCategory, qint32 errorCode, const QString &errorMessage)
{
    NetworkErrorResponse *error = new NetworkErrorResponse(errorCategory, errorCode, errorMessage, m_request);
    emit m_request->didReceiveError(error);
}

}
}
