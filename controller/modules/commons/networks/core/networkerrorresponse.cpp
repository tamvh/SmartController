#include "networkerrorresponse.h"

namespace Network {
namespace Core {

NetworkErrorResponse::NetworkErrorResponse(NetworkError errorCategory, qint32 errorCode, const QString &errorMessage, QObject *parent) :
    QObject(parent),
    m_errorCategory(errorCategory),
    m_errorCode(errorCode),
    m_errorMessage(errorMessage)
{
}

}
}
