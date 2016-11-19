#include "httpclient.h"


HttpClient::HttpClient(QObject* parent)
    : QObject(parent)
{
}

HttpClient::~HttpClient()
{
}

void HttpClient::initialize(const QString& host, int port) {
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    _host = host;
    _port = port;   
    _method = HttpRequestMethod::GET; //defallt
}

void HttpClient::setRequestMethod(HttpRequestMethod requestMethod) {
    _method = requestMethod;
}

void HttpClient::addPostItem(const QString &key, const QString &value) {
    if (!_m_postData.isEmpty()) {
        _m_postData.append(",");
    }

    _m_postData.append(key);
    _m_postData.append(":");
    _m_postData.append(value);
}

void HttpClient::sendRequest(const QString& api, QByteArray m_postData) {
    QString url = "http://" + _host + ":" + QString::number(_port) + "/" + api;
    qDebug() << "Url: " + url;
    QNetworkAccessManager * mgr = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest();
    request->setUrl(QUrl(url));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "some/type");

    switch (_method) {
    case HttpRequestMethod::GET:
        _repData = mgr->get(*request);
        break;
    case HttpRequestMethod::POST:
        m_postData = "{" + m_postData + "}";
        _repData = mgr->post(*request, m_postData);
        break;
    default:
        break;
    }
}

QNetworkReply* HttpClient::replyData() {
    return _repData;
}
