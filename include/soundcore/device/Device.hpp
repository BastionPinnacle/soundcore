#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

class Device : public QObject {
    Q_OBJECT
public:
    Device(QObject* parent = nullptr);
    void setup();
    ~Device();
    signals:
    void finalizeConnect();
    void finalizeDisconnect();
public slots:
    void onInitiateConnect(QBluetoothDeviceInfo device_info);
    void onInitateDisconnect();
    void onSendMessage(QByteArray message);
private:
    QBluetoothServiceDiscoveryAgent service_discovery_agent;
    QBluetoothSocket* socket = nullptr;
};
