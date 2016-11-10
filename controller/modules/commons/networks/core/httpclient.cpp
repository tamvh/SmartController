#include "httpclient.h"

class HttpClient::Impl {
public:
    QByteArray m_postData;
    QNetworkReply *repData;
    QNetworkAccessManager * mgr;
    QNetworkRequest *request;
    HttpRequestMethod method;
    QString host;
    int port;

};
HttpClient::HttpClient(const QString& host, int port) :
    d_ptr(new Impl)
{
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    d_ptr->host = host;
    d_ptr->port = port;
    d_ptr->request->setHeader(QNetworkRequest::ContentTypeHeader, "some/type");

}

HttpClient::~HttpClient()
{
}

void HttpClient::setRequestMethod(HttpRequestMethod requestMethod) {
    d_ptr->method = requestMethod;
}

void HttpClient::addPostItem(const QString &key, const QString &value) {
    if (!d_ptr->m_postData.isEmpty()) {
        d_ptr->m_postData.append(",");
    }

    d_ptr->m_postData.append(key);
    d_ptr->m_postData.append(":");
    d_ptr->m_postData.append(value);
}

void HttpClient::sendRequest(const std::string& api) {
    d_ptr->request->setUrl(d_ptr->host+":" + QString::number(d_ptr->port) + "/" + api);
    switch (d_ptr->method) {
    case HttpRequestMethod::GET:
        d_ptr->repData = d_ptr->mgr->get(d_ptr->request);
        break;
    case HttpRequestMethod::POST:
        d_ptr->repData = d_ptr->mgr->post(d_ptr->request, d_ptr->m_postData);
        break;
    default:
        break;
    }
}

QNetworkReply* HttpClient::replyData() {
    return d_ptr->m_postData;
}
