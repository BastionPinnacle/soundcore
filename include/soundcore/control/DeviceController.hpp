#pragma once

#include<QObject>
#include<QHash>

class DeviceController : public QObject
{
public:
    Q_PROPERTY(QStringList profile_keys READ profileKeys CONSTANT)
    Q_PROPERTY(QStringList mode_keys READ modeKeys CONSTANT)
    QStringList profileKeys() const;
    QStringList modeKeys() const ;
    signals:
    void sendMessage(QByteArray message);
private slots:
    void onProfileKeyChosen(QString profile);
    void onModeKeyChosen(QString mode);
private:
    const static QHash<QString, QString> equalizer_profiles;
    const static QHash<QString, QString> modes;
};
