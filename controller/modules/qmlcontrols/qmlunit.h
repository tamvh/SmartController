#ifndef QMLUNIT_H
#define QMLUNIT_H

#include <QObject>

class QmlUnit : public QObject
{
    Q_OBJECT
public:
    explicit QmlUnit(QObject *parent = 0);
    ~QmlUnit();

    Q_INVOKABLE float dp(float value) const {
        return value * screenDensity_;
    }

    Q_INVOKABLE float sp(float value) const {
        return value * fontScaledDensity_;
    }
signals:

public slots:
private:
    float screenDensity_;
    float fontScaledDensity_;
};

#endif // QMLUNIT_H
