#ifndef BLUETOOTHOPERATION_H
#define BLUETOOTHOPERATION_H

#include <QObject>
#include <QSharedPointer>
class BluetoothCharacteristic;
class BluetoothService;
class BluetoothOperation: public QObject
{
    Q_OBJECT
public:
    explicit BluetoothOperation(const QString &service,
                                const QString &characteristic,
                                QObject *parent = 0);
public:
    typedef QMap<QString, BluetoothService *> Services;
    bool execute(Services &services);
    const QString &service() const;
    const QString &characteristic() const;
signals:
    void executed(BluetoothOperation *operation);
private:
    virtual bool execute(BluetoothCharacteristic &characteristic,
                         BluetoothService &service) = 0;
    virtual void finish() = 0;
private:
    friend class BluetoothController;
    class Private;
    QSharedPointer<Private> d_ptr;
    Q_DECLARE_PRIVATE()
};


/**
 * @brief The BluetoothWrite class
 */
class BluetoothWrite: public BluetoothOperation
{
    Q_OBJECT
public:
    BluetoothWrite(const QString &service,
                   const QString &characteristic,
                   const int &value,
                   QObject *parent = 0);

    inline int value() const {
        return _value;
    }
signals:
    void written(QString service,
                 QString characteristic,
                 int value);
private:
    virtual bool execute(BluetoothCharacteristic &characteristic,
                         BluetoothService &service);
    virtual void finish();
private:
    int _value;
};


/**
 * @brief The BluetoothRead class
 */
class BluetoothRead: public BluetoothOperation
{
    Q_OBJECT
public:
    explicit BluetoothRead(const QString &service,
                           const QString &characteristic,
                           QObject *parent = 0);

    inline int value() const {
        return _value;
    }

    inline void setValue(int value) {
        _value = value;
    }

signals:
    void readed(QString service,
                QString characteristic,
                int value);
private:
    virtual bool execute(BluetoothCharacteristic &characteristic,
                         BluetoothService &service);
    virtual void finish();
private:
    int _value;
};

#endif // BLUETOOTHOPERATION_H
