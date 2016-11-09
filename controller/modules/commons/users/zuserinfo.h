#ifndef ZUSERINFO_H
#define ZUSERINFO_H

#include <QObject>

class ZUserInfoPrivate;

class ZUserInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 userID READ userID NOTIFY userIDChanged)
    Q_PROPERTY(QString userName READ userName NOTIFY userNameChanged)
    Q_PROPERTY(QString avatar READ avatar NOTIFY avatarChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString userSession READ userSession NOTIFY userSessionChanged)

    Q_PROPERTY(bool isValid READ hasValidUserInfo NOTIFY isValidChanged)

public:
    explicit ZUserInfo(QObject *parent = 0);
    ~ZUserInfo();
public:
    bool reloadCurrentUser();
public:
    Q_INVOKABLE bool isLoggedIn() const;
    Q_INVOKABLE void logout();
    bool hasValidUserInfo() const;
    QString userName() const;
    QString avatar() const;
    QString displayName() const;
    QString userSession() const;
    quint64 userID() const;
signals:
    void userIDChanged();
    void userNameChanged();
    void avatarChanged();
    void displayNameChanged();
    void userSessionChanged();
    void isValidChanged();
    void loadUserInfoSuccess();
    void loadUserInfoError();
public slots:
private slots:
private:
    ZUserInfoPrivate *p;
};

ZUserInfo* getCurrentUser();

#endif // ZUSERINFO_H
