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
    Worker(QObject *parent = nullptr) {
        connect(&m_service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                         [this](QBluetoothServiceInfo service_info) {
                             if (service_info.serviceName() == "Serial Port Profile") {
                                 m_socket.setSocketDescriptor(m_socket.socketDescriptor(),
                                                              QBluetoothServiceInfo::RfcommProtocol);
                                 m_socket.connectToService(service_info);
                             }
                         });
        connect(&receive_timer, &QTimer::timeout, [this]() {
            if(connected)
            {
                auto received = m_socket.read(MAX_READ_LENGTH);
                qDebug() << received;
                receive_buffer.append(received);
            }
        });
        connect(&transmit_timer, &QTimer::timeout, [this]() {
            if(connected){
                auto number_of_bytes_sent = m_socket.write(transmit_buffer);
                transmit_buffer = transmit_buffer.mid(number_of_bytes_sent);
            }
        });
        connect(&get_state_timer, &QTimer::timeout, [this]() {
            if(connected)
            {
                m_socket.write(get_state_message);
            }
        });
        connect(&m_socket, &QBluetoothSocket::connected, this, &Worker::onConnectedSocket);
        connect(&m_socket, &QBluetoothSocket::disconnected, this, &Worker::onDisconnectedSocket);
        receive_timer.setInterval(100);
        transmit_timer.setInterval(100);
        get_state_timer.setInterval(100);
    }

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

private:
    const static QByteArray get_state_message;
    QBluetoothServiceDiscoveryAgent m_service_discovery_agent;
    QBluetoothSocket m_socket;
    QByteArray receive_buffer;
    QByteArray transmit_buffer;
    QTimer receive_timer;
    QTimer transmit_timer;
    QTimer get_state_timer;
    bool connected = false;
};

const QByteArray Worker::get_state_message = "08ee00000001010a0002";

void Worker::onInitiateConnect(QBluetoothDeviceInfo device_info) {
    m_service_discovery_agent.clear();
    m_service_discovery_agent.setRemoteAddress(device_info.address());
    m_service_discovery_agent.start();
}

void Worker::onInitiateDisconnect() {
    m_socket.disconnectFromService();
}

void Worker::onConnectedSocket() {
    m_service_discovery_agent.stop();
    connected = true;
    emit finalizeConnect();
}

void Worker::onDisconnectedSocket() {
    connected = false;
    emit finalizeDisconnect();
}

void Worker::onSendMessage(QByteArray message) {
    transmit_buffer.append(message);
}


class Controller : public QObject {
Q_OBJECT

    QThread
            workerThread;
public:
    Controller(QObject* parent = nullptr) {
        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::initiateConnect, worker, &Worker::onInitiateConnect);
        connect(this, &Controller::initiateDisconnect, worker, &Worker::onInitiateDisconnect);
        connect(this, &Controller::sendMessage, worker, &Worker::onSendMessage);
        connect(worker, &Worker::finalizeDisconnect, this, &Controller::onFinalizeDisconnect);

        workerThread.start();
    }

    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }

public
    slots:
    void onInitiateConnect(QBluetoothDeviceInfo device_info);

    void onInitiateDisconnect();

    void onSendMessage(QByteArray message);

    void onFinalizeConnect();

    void onFinalizeDisconnect();

signals:
    void finalizeConnect();

    void finalizeDisconnect();

    void sendMessage(QByteArray message);

    void initiateConnect(QBluetoothDeviceInfo device_info);

    void initiateDisconnect();

};

void Controller::onSendMessage(QByteArray message) {
    emit sendMessage(message);
}

void Controller::onInitiateDisconnect() {
    emit initiateDisconnect();
}

void Controller::onInitiateConnect(QBluetoothDeviceInfo device_info) {
    emit initiateConnect(device_info);
}

void Controller::onFinalizeConnect() {
    emit finalizeConnect();
}

void Controller::onFinalizeDisconnect() {
    emit finalizeDisconnect();
}