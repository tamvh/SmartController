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
enum HttpRequestMethod {
    POST,
    GET
};

class HttpClient : public QObject
{
    Q_OBJECT
public:
    HttpClient(QObject* parent = 0);
    virtual ~HttpClient();
public:
    void initialize(const QString& host, int port);
    void setRequestMethod(HttpRequestMethod requestMethod);
    void addPostItem(const QString &key, const QString &value);
    void sendRequest(const QString& api, QByteArray m_postData);
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
