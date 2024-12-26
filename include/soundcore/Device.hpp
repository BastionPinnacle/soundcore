#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>

class Device : public QObject {
Q_OBJECT
public:
    Device() = delete;
    Device(const QBluetoothDeviceInfo& device_info);

    Q_INVOKABLE bool connect();
    Q_INVOKABLE void disconnect();
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(bool status READ status NOTIFY statusChanged)
    QString name() const;
    bool status() const;
signals:
    void nameChanged();
    void statusChanged();
private:
    QBluetoothDeviceInfo device_info;
    QBluetoothSocket* socket;
};
