#ifndef NETWORKERRORRESPONSE_H
#define NETWORKERRORRESPONSE_H

#include <QObject>
#include <QString>
#include "networkerror.h"

namespace Network {
namespace Core {

class NetworkErrorResponse : public QObject
{
    Q_OBJECT
public:
    explicit NetworkErrorResponse(NetworkError errorCategory, qint32 errorCode, const QString &errorMessage, QObject *parent = 0);
public:
    NetworkError errorCategory() const { return m_errorCategory; }
    qint32 errorCode() const { return m_errorCode; }
    QString errorMessage() const { return m_errorMessage; }
private:
    NetworkError m_errorCategory;
    qint32 m_errorCode;
    QString m_errorMessage;
};

}
}

#endif // NETWORKERRORRESPONSE_H
