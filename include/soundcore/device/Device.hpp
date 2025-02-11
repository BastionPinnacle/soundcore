#pragma once

#include <QObject>
#include <QThread>
#include <QBluetoothServiceInfo>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QMutex>
#include <QTimer>

#define MAX_READ_LENGTH 1024

class Worker : public QObject {
Q_OBJECT

public:
    void setup();

public slots:

    void onInitiateConnect(QBluetoothDeviceInfo device_info);

    void onInitiateDisconnect();

    void onSendMessage(QByteArray message);

private slots:

    void onConnectedSocket();

    void onDisconnectedSocket();

signals:

    void finalizeConnect();

    void finalizeDisconnect();

    void receivedMessage(QByteArray message);

private:
    const static QByteArray get_state_message;
    QBluetoothServiceDiscoveryAgent* m_service_discovery_agent;
    QBluetoothSocket* m_socket;
    QByteArray transmit_buffer;
    QTimer* receive_timer;
    QTimer* transmit_timer;
    QTimer* get_state_timer;
    bool connected = false;
};

class Device : public QObject {
Q_OBJECT

    QThread worker_thread;
public:
    Device();

    ~Device();

public
    slots:

    void onInitiateConnect(QBluetoothDeviceInfo device_info);

    void onInitiateDisconnect();

    void onSendMessage(QByteArray message);

    void onReceivedMessage(QByteArray message);

    void onFinalizeConnect();

    void onFinalizeDisconnect();

signals:

    void finalizeConnect();

    void finalizeDisconnect();

    void sendMessage(QByteArray message);

    void receivedMessage(QByteArray message);

    void initiateConnect(QBluetoothDeviceInfo device_info);

    void initiateDisconnect();

};