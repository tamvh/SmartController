#include "bluetoothcontroller.h"
#include "bluetoothoperation.h"
#include <QDebug>
#include <QList>
#include <QMap>
class BluetoothController::Private
{
public:
    Private():
        _sending(NULL),
        _pending(NULL) {

    }
    virtual ~Private() {
        clear();
    }

    void schedule(BluetoothOperation *operation) {
        _pending = operation;
    }


    bool writing() {
        return _sending == NULL;
    }

    void clear() {
        if (_sending != NULL)
            _sending = NULL;

        if (_pending != NULL)
            _pending = NULL;
    }

    void execute(BluetoothOperation::Services *services) {
        if (_sending != NULL || _pending == NULL)
            return;
        _sending = _pending;
        _pending = NULL;
        QObject::connect(_sending,
                         &BluetoothWrite::executed,
                         [this, services](BluetoothOperation *operation) {
            operation->finish();
            this->finish();
            this->execute(services);
        });
        _sending->execute(*services);
    }

private:
    void finish() {
        _sending = NULL;
    }

public:
    BluetoothOperation *_sending;
    BluetoothOperation *_pending;
};

BluetoothController::BluetoothController():
    d_ptr(new Private)
{

}

void BluetoothController::schedule(BluetoothOperation *operation)
{
    Q_D();
    d->schedule(operation);
}

void BluetoothController::execute(Services *services)
{
    Q_D();
    d->execute(services);
}

void BluetoothController::reset()
{
    Q_D();
    d->clear();
}
