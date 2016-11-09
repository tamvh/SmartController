#ifndef ZSTACKBRIGHT_H
#define ZSTACKBRIGHT_H

#include <cstdint>
#include <memory>
#include <QString>


class ZQueueBright
{
public:
    ZQueueBright();
    ZQueueBright(const QString &deviceAddress, const int percentBright);
    ZQueueBright(const ZQueueBright& other);
    ZQueueBright& operator=(const ZQueueBright& other);
    bool operator==(const ZQueueBright& other) const;
    bool operator==(const QString deviceAddress) const;

    int getPercentBright() const;
    void setPercentBright(const int value);

    QString getDeviceAddress() const;
    void setDeviceAddress(const QString &deviceAddress);

private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

inline bool operator==(const ZQueueBright &a1, const QString &a2)
{ return a1.getDeviceAddress() == a2; }
inline bool operator==(const QString &a2, const ZQueueBright &a1)
{ return a1.getDeviceAddress() == a2; }


#endif // ZSTACKBRIGHT_H
