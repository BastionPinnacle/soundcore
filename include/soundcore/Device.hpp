#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

class Device : public QObject {
Q_OBJECT
public:
    Device(const QBluetoothDeviceInfo& device_info,QObject* parent=nullptr);
    Q_INVOKABLE void tryToConnect();
    Q_INVOKABLE void tryToDisconnect();
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    QString name() const;
    void setup();
    ~Device();
signals:
    void nameChanged();
    void connected();
    void disconnected();
private:
    QBluetoothDeviceInfo device_info;
    QBluetoothServiceDiscoveryAgent service_discovery_agent;
    QBluetoothSocket* socket = nullptr;
};
