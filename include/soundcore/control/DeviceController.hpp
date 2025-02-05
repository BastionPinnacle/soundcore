#pragma once

#include<QObject>
#include<QHash>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QStringList profile_keys READ profileKeys CONSTANT)
    Q_PROPERTY(QStringList mode_keys READ modeKeys CONSTANT)
    Q_PROPERTY(bool control_available MEMBER m_control_available READ controlAvailable NOTIFY controlAvailableChanged)
    Q_INVOKABLE void disconnectDevice();
    QStringList profileKeys() const;
    QStringList modeKeys() const;
    bool controlAvailable() const;
    signals:
    void sendMessage(QByteArray message);
    void controlAvailableChanged();
    void initiateDisconnect();
public slots:
    void onFinalizeConnect();
    void onFinalizeDisconnect();
private slots:
    void onProfileKeyChosen(QString profile);
    void onModeKeyChosen(QString mode);
private:
    const static QHash<QString, QString> m_equalizer_profiles;
    const static QHash<QString, QString> m_modes;
    bool m_control_available = false;
};

