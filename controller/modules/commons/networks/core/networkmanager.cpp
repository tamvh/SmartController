#include "networkmanager.h"
#include "networkresponse.h"
#include "networkrequest.h"
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Network {
namespace Core {

static NetworkManager *staticInstance = NULL;

NetworkManager *NetworkManager::instance() {
    if (staticInstance == NULL) {
        staticInstance = new NetworkManager();
    }
    return staticInstance;
}

NetworkManager::NetworkManager():
    m_networkAccessManager(this)
{

}

void NetworkManager::initialize()
{
}

void NetworkManager::enqueueRequest(NetworkRequest *request)
{
    QNetworkReply *reply = request->enqueue(&m_networkAccessManager);
    connect(reply, SIGNAL(finished()), this, SLOT(receiveReply()));
}

void NetworkManager::receiveReply()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    NetworkRequest *request = (NetworkRequest *)reply->request().originatingObject();
    request->responseObject()->setReplyData(reply);
    reply->deleteLater();
    request->deleteLater();
}

}
}
