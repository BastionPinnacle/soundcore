#pragma once

#include<QObject>
#include<QMap>


class DeviceController : public QObject {
Q_OBJECT

public:
    Q_PROPERTY(QStringList profile_keys READ profileKeys CONSTANT)
    Q_PROPERTY(QStringList mode_keys READ modeKeys CONSTANT)
    Q_PROPERTY(QList<int> kHz MEMBER m_kHz READ kHz NOTIFY kHzChanged)
    Q_PROPERTY(bool control_available MEMBER m_control_available READ controlAvailable NOTIFY controlAvailableChanged)
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE void chooseProfile(QString profile);
    Q_INVOKABLE void chooseMode(QString profile);
    Q_INVOKABLE void updateValue(int index, int value);

    DeviceController(QObject *parent = nullptr);

    QStringList profileKeys() const;

    QStringList modeKeys() const;

    QList<int> kHz();

    bool controlAvailable() const;

signals:

    void sendMessage(QByteArray message);

    void controlAvailableChanged();

    void initiateDisconnect();

    void kHzChanged();

public slots:

    void onFinalizeConnect();

    void onFinalizeDisconnect();

    void onKHzChanged();

    void onReceivedMessage(QByteArray message);

private:
    const static QMap<QString, QString> m_equalizer_profiles;
    const static QMap<QString, QString> m_modes;
    const static QByteArray m_ack_message;
    bool m_control_available = false;
    QList<int> m_kHz = {120,120,120,120,120,120,120,120};
};

