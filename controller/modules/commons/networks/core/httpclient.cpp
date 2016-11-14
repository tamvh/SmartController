#include "httpclient.h"


HttpClient::HttpClient()
{    
}

HttpClient::~HttpClient()
{
}

void HttpClient::init(const QString& host, int port) {
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    _host = host;
    _port = port;
    _request->setHeader(QNetworkRequest::ContentTypeHeader, "some/type");
    _method = HttpRequestMethod::POST;
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

void HttpClient::sendRequest(const QString& api) {
    _request->setUrl(QUrl(_host + ":" + QString::number(_port) + "/" + api));
    switch (_method) {
    case HttpRequestMethod::GET:
        _repData = _mgr->get(*_request);
        break;
    case HttpRequestMethod::POST:
        _m_postData = "{" + _m_postData + "}";
        _repData = _mgr->post(*_request, _m_postData);
        break;
    default:
        break;
    }
}

QNetworkReply* HttpClient::replyData() {
    return _repData;
}
