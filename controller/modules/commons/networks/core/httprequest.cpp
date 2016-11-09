#include <QDebug>
#include <QtGui/QGuiApplication>
#include "httprequest.h"
#include "networkresponse.h"
#include "networkmanager.h"

QString getCurrentUserSession();

namespace Network {
namespace Core {

HttpRequest::HttpRequest(const QString &basedUrl, const QString &path, NetworkResponse *transferedResponse, QObject *parent):
    NetworkRequest(parent),
    m_request(new QNetworkRequest()),
    m_response(transferedResponse),
    m_basedUrl(basedUrl),
    m_path(path),
    m_requestMethod(HttpRequestMethod::GET),
    m_shouldIncludeSessionKey(true)
{
    m_request->setOriginatingObject(this);
}

HttpRequest::~HttpRequest()
{
    qDebug() << "destructor HttpRequest";
}

NetworkResponse* HttpRequest::responseObject()
{
    return m_response.data();
}

HttpRequestMethod HttpRequest::requestMethod() const
{
    return m_requestMethod;
}

void HttpRequest::setRequestMethod(HttpRequestMethod requestMethod)
{
    m_requestMethod = requestMethod;
}

void HttpRequest::setShouldIncludeSessionKey(bool value)
{
    m_shouldIncludeSessionKey = value;
}

QNetworkReply* HttpRequest::enqueue(QNetworkAccessManager *manager)
{
    QNetworkReply* returnValue;
    QNetworkRequest *requestObject = m_request.data();
    initializeUrl();
    m_request->setUrl(m_url);
    switch (m_requestMethod) {
    case HttpRequestMethod::GET:
        qDebug() << "GET --- " << requestObject->url();
        returnValue = manager->get(*requestObject);
        break;
    case HttpRequestMethod::POST:
        qDebug() << "POST --- " << requestObject->url();
        returnValue = manager->post(*requestObject, m_postData);
        break;
    default:
        returnValue = nullptr;
        break;
    }

    return returnValue;
}

QNetworkRequest* HttpRequest::requestObject()
{
    return m_request.data();
}

QByteArray HttpRequest::postData() const
{
    return m_postData;
}

void HttpRequest::setPostData(const QByteArray &data)
{
    m_postData = data;
}

void HttpRequest::addPostItem(const QString &key, const QString &value)
{
    if (!m_postData.isEmpty()) {
        m_postData.append("&");
    }

    m_postData.append(key);
    m_postData.append("=");
    m_postData.append(value);
}

void HttpRequest::addQueryItem(const QString &key, const QString &value)
{
    m_parameters.addQueryItem(key, value);
}

void HttpRequest::initializeUrl()
{
    if (!m_url.isEmpty()) {
        return;
    }
    QString combined = m_basedUrl + m_path;
    combined = combined.replace("://", ":$$");
    combined = combined.replace("//", "/");
    combined = combined.replace(":$$", "://");
    m_url = QUrl(combined);

    QUrlQuery query(m_url);
    for (QPair<QString, QString> keyValue : query.queryItems()) {
        if (!m_parameters.hasQueryItem(keyValue.first)) {
            m_parameters.addQueryItem(keyValue.first, keyValue.second);
        }
    }

    if (m_shouldIncludeSessionKey) {
        QString userSession = getCurrentUserSession();
        if (m_postData.isEmpty()) {
            if (!userSession.isEmpty()) {
                addQueryItem("session_key", userSession);
            }
            addQueryItem("ostype", QGuiApplication::platformName());
        } else {
            if (!userSession.isEmpty()) {
                addPostItem("session_key", userSession);
            }
            addPostItem("ostype", QGuiApplication::platformName());
        }
    }

    m_url.setQuery(m_parameters);
}

}
}
