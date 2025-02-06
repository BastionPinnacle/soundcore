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
    signals:
    void finalizeConnect();
    void finalizeDisconnect();
public slots:
    void onInitiateConnect(QBluetoothDeviceInfo device_info);
    void onInitiateDisconnect();
    void onSendMessage(QByteArray message);
private slots:
    void onConnectedSocket();
    void onDisconnectedSocket();
private:
    QBluetoothServiceDiscoveryAgent m_service_discovery_agent;
    QBluetoothSocket m_socket;
};
