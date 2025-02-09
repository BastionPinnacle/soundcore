#pragma once

#include<QObject>
#include<QMap>

struct Loudness {
    int m_kHz100 = 0;
    int m_kHz200 = 0;
    int m_kHz400 = 0;
    int m_kHz800 = 0;
    int m_kHz1600 = 0;
    int m_kHz3200 = 0;
    int m_kHz6400 = 0;
    int m_kHz12800 = 0;
};

class DeviceController : public QObject {
Q_OBJECT

public:
    Q_PROPERTY(QStringList profile_keys READ profileKeys CONSTANT)
    Q_PROPERTY(QStringList mode_keys READ modeKeys CONSTANT)
    Q_PROPERTY(bool control_available MEMBER m_control_available READ controlAvailable NOTIFY controlAvailableChanged)
    Q_PROPERTY(int kHz100 READ kHz100 NOTIFY kHz100Changed)
    Q_PROPERTY(int kHz200 READ kHz200 NOTIFY kHz200Changed)
    Q_PROPERTY(int kHz400 READ kHz400 NOTIFY kHz400Changed)
    Q_PROPERTY(int kHz800 READ kHz800 NOTIFY kHz800Changed)
    Q_PROPERTY(int kHz1600 READ kHz1600 NOTIFY kHz1600Changed)
    Q_PROPERTY(int kHz3200 READ kHz3200 NOTIFY kHz3200Changed)
    Q_PROPERTY(int kHz6400 READ kHz6400 NOTIFY kHz6400Changed)
    Q_PROPERTY(int kHz12800 READ kHz12800 NOTIFY kHz12800Changed)
    Q_INVOKABLE void disconnectDevice();

    Q_INVOKABLE void chooseProfile(QString profile);

    Q_INVOKABLE void chooseMode(QString profile);

    DeviceController(QObject *parent = nullptr);

    QStringList profileKeys() const;

    QStringList modeKeys() const;

    int kHz100() const;

    int kHz200() const;

    int kHz400() const;

    int kHz800() const;

    int kHz1600() const;

    int kHz3200() const;

    int kHz6400() const;

    int kHz12800() const;

    bool controlAvailable() const;

signals:

    void sendMessage(QByteArray message);

    void controlAvailableChanged();

    void initiateDisconnect();

    void kHz100Changed(int khz);

    void kHz200Changed(int khz);

    void kHz400Changed(int khz);

    void kHz800Changed(int khz);

    void kHz1600Changed(int khz);

    void kHz3200Changed(int khz);

    void kHz6400Changed(int khz);

    void kHz12800Changed(int khz);

public slots:

    void onFinalizeConnect();

    void onFinalizeDisconnect();

private:
    const static QMap<QString, QString> m_equalizer_profiles;
    const static QMap<QString, QString> m_modes;
    bool m_control_available = false;
    Loudness m_loudness;
};

