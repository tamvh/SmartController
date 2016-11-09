#ifndef BLUETOOTHWRITER_H
#define BLUETOOTHWRITER_H
#include <QSharedPointer>
class BluetoothOperation;
class BluetoothService;
class QBluetoothUuid;
class BluetoothController
{
public:
    typedef QMap<QString, BluetoothService *> Services;
    BluetoothController();
public:
    void schedule(BluetoothOperation *operation);
    void execute(Services *services);
    void reset();
private:
    class Private;
    QSharedPointer<Private> d_ptr;
    Q_DECLARE_PRIVATE()
};

#endif // BLUETOOTHWRITER_H
