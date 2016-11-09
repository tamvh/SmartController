#ifndef SMARTTHINGS_NETWORKMANAGER_H
#define SMARTTHINGS_NETWORKMANAGER_H
#include <QObject>
#include <QNetworkAccessManager>

#include "networkrequest.h"

namespace Network {
namespace Core {

class NetworkManager :public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager();
public:
    static NetworkManager *instance();
public:
    void enqueueRequest(NetworkRequest *request);
private slots:
    void receiveReply();
private:
    void initialize();
private:
    QNetworkAccessManager m_networkAccessManager;
};

}
}


#endif // SMARTTHINGS_NETWORKMANAGER_H
