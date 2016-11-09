#include "httpjsonresponse.h"
#include "networkerrorresponse.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace Network {
namespace Core {

HttpJsonResponse::HttpJsonResponse(NetworkRequest *request):
    NetworkResponse(request)
{
}

bool HttpJsonResponse::parseData(QNetworkReply *reply)
{
    QJsonParseError error;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll(), &error);

    if (error.error != QJsonParseError::NoError) {
        reportError(NetworkErrorInvalidJson, (qint32)error.error, error.errorString());
        return false;
    }

    if (jsonResponse.isEmpty()) {
        reportError(NetworkErrorEmptyResponse, 0, "Empty response");
        return false;
    }

    if (!jsonResponse.isObject()) {
        reportError(NetworkErrorInvalidResponse, 0, "Missing the \"properties\" map");
        return false;
    }

    QJsonObject jsonObject = jsonResponse.object();
    m_responseData = jsonObject;

    if (!jsonObject.contains("error_code")) {
        reportError(NetworkErrorMissingParameter, 0, ("Missing the \"error_code\" field"));
        return false;
    }

    QJsonValue errorCode = jsonObject.value("error_code");
    if (!errorCode.isDouble()) {
        reportError(NetworkErrorInvalidParameter, 0, ("The \"error_code\" field invalid"));
        return false;
    }

    if (errorCode.toInt() != 0) {
        QJsonValue message = jsonObject.value("error_message");
        reportError(NetworkErrorServerError, errorCode.toInt(), message.toString());
        return false;
    }

//    if (!jsonObject.contains("data")) {
//        reportError(NetworkErrorMissingParameter, 0, ("The \"data\" field is missed"));
//        return false;
//    }

    QJsonValue dataValue = jsonObject.value("data");
    return parseData(dataValue);
}

bool HttpJsonResponse::parseData(QJsonValue &data)
{
    Q_UNUSED(data)
    return true;
}

}
}
