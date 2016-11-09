#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QUrlQuery>
#include <QString>
#include <QSharedPointer>
#include <QNetworkRequest>

#include "networkrequest.h"

namespace Network {
namespace Core {

enum class HttpRequestMethod {
    GET,
    POST
};

class HttpRequest : public NetworkRequest
{
public:
    explicit HttpRequest(const QString &basedUrl, const QString &path, NetworkResponse *transferedResponse, QObject *parent = 0);
    virtual ~HttpRequest();
public:
    virtual QNetworkRequest* requestObject();
    virtual NetworkResponse* responseObject();
    virtual QNetworkReply* enqueue(QNetworkAccessManager *manager);
public:
    QByteArray postData() const;
    HttpRequestMethod requestMethod() const;
public:
    void addPostItem(const QString &key, const QString &value);
    void addQueryItem(const QString &key, const QString &value);
protected:
    void setPostData(const QByteArray& data);
    void setRequestMethod(HttpRequestMethod requestMethod);
    void setShouldIncludeSessionKey(bool value);
private:
    void initializeUrl();
private:
    QSharedPointer<QNetworkRequest> m_request;
    QSharedPointer<NetworkResponse> m_response;
    QByteArray m_postData;
    QString m_basedUrl;
    QString m_path;
    QUrlQuery m_parameters;
    HttpRequestMethod m_requestMethod;
    QUrl m_url;
    bool m_shouldIncludeSessionKey;
};

}
}

#endif // HTTPREQUEST_H
