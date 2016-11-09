#include "zstackbright.h"

class ZQueueBright::Impl {
public:
    QString deviceAddress;
    int currentBright;
};

ZQueueBright::ZQueueBright() :
    d_ptr(new Impl)
{

}

ZQueueBright::ZQueueBright(const QString &deviceAddress, const int currentBright) {
    d_ptr->deviceAddress = deviceAddress;
    d_ptr->currentBright = currentBright;
}

ZQueueBright::ZQueueBright(const ZQueueBright& other) :
    d_ptr(other.d_ptr)
{

}

ZQueueBright& ZQueueBright::operator=(const ZQueueBright& other) {
    d_ptr = other.d_ptr;
    return *this;
}

bool ZQueueBright::operator==(const ZQueueBright& other) const {
    return d_ptr->deviceAddress == other.getDeviceAddress();
}

bool ZQueueBright::operator==(const QString deviceAddress) const {
    return d_ptr->deviceAddress == deviceAddress;
}

QString ZQueueBright::getDeviceAddress() const {
    return d_ptr->deviceAddress;
}

void ZQueueBright::setDeviceAddress(const QString &deviceAddress) {
    d_ptr->deviceAddress = deviceAddress;
}

int ZQueueBright::getPercentBright() const {
    return d_ptr->currentBright;
}

void ZQueueBright::setPercentBright(const int value) {
    d_ptr->currentBright = value;
}
