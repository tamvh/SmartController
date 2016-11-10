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
    HttpClient(const QString& host, int port);
    virtual ~HttpClient();
public:
    void setRequestMethod(HttpRequestMethod requestMethod);
    void addPostItem(const QString &key, const QString &value);
    void sendRequest(const std::string& api);
    QNetworkReply* replyData();
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // HTTPCLIENT_H
