#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <iostream>
#include <memory>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QLoggingCategory>

enum class HttpRequestMethod {
    GET,
    POST
};

class HttpClient
{
public:
    HttpClient();
    virtual ~HttpClient();
public:
    void init(const QString& host, int port);
    void setRequestMethod(HttpRequestMethod requestMethod);
    void addPostItem(const QString &key, const QString &value);
    void sendRequest(const QString& api);
    QNetworkReply* replyData();
private:
    QByteArray _m_postData;
    QNetworkReply *_repData;
    QNetworkAccessManager *_mgr;
    QNetworkRequest *_request;
    HttpRequestMethod _method;
    QString _host;
    int _port;
};

#endif // HTTPCLIENT_H
