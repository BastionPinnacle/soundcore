#include "soundcore/device/Device.hpp"

const QByteArray Worker::get_state_message = QByteArray::fromHex("08ee00000001010a0002");

void Worker::onInitiateConnect(QBluetoothDeviceInfo device_info) {
    //qDebug() << "Initiate connect" <<  QThread::currentThread();
    if(!m_socket)
    {
        m_socket = new QBluetoothSocket(nullptr);
        connect(m_socket, &QBluetoothSocket::connected, this, &Worker::onConnectedSocket);
        connect(m_socket, &QBluetoothSocket::disconnected, this, &Worker::onDisconnectedSocket);
    }
    if(!m_service_discovery_agent)
    {
        m_service_discovery_agent = new QBluetoothServiceDiscoveryAgent(nullptr);
        connect(m_service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                [this](QBluetoothServiceInfo service_info) {
                    if (service_info.serviceName() == "Serial Port Profile") {
                        m_socket->setSocketDescriptor(m_socket->socketDescriptor(),
                                                      QBluetoothServiceInfo::RfcommProtocol);
                        m_socket->connectToService(service_info);
                    }
                });

    }
    if(!receive_timer)
    {
        receive_timer = new QTimer(nullptr);
        connect(receive_timer, &QTimer::timeout, [this]() {
            if (connected) {
                auto received = m_socket->read(MAX_READ_LENGTH);
                if(received.size()>0)
                {
                    //qDebug() << received.toHex();
                }
                receive_buffer.append(received);
            }
        });
    }
    if(!transmit_timer)
    {
        transmit_timer = new QTimer(nullptr);
        connect(transmit_timer, &QTimer::timeout, [this]() {
            if (connected) {
                if(transmit_buffer.size()>0)
                {
                    //qDebug() << transmit_buffer.toHex();
                }
                auto number_of_bytes_sent = m_socket->write(transmit_buffer);
                transmit_buffer = transmit_buffer.mid(number_of_bytes_sent);
            }
        });
    }
    if(!get_state_timer)
    {
        get_state_timer = new QTimer(nullptr);
        connect(get_state_timer, &QTimer::timeout, [this]() {
            if (connected) {
                transmit_buffer.append(get_state_message);
            }
        });
    }

    receive_timer->setInterval(100);
    transmit_timer->setInterval(100);
    get_state_timer->setInterval(500);
    m_service_discovery_agent->clear();
    m_service_discovery_agent->setRemoteAddress(device_info.address());
    m_service_discovery_agent->start();
}

void Worker::onInitiateDisconnect() {
    m_socket->disconnectFromService();
}

void Worker::onConnectedSocket() {
    m_service_discovery_agent->stop();
    //qDebug() << "CONNECTED socket";
    connected = true;
    receive_timer->start();
    transmit_timer->start();
    get_state_timer->start();
    emit finalizeConnect();
}

void Worker::onDisconnectedSocket() {
    connected = false;
    emit finalizeDisconnect();
}

void Worker::onSendMessage(QByteArray message) {
    transmit_buffer.append(message);
}


Device::Device() {
    Worker *worker = new Worker();
    //qDebug() << &worker_thread;
    worker->moveToThread(&worker_thread);
    connect(&worker_thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Device::initiateConnect, worker, &Worker::onInitiateConnect);
    connect(this, &Device::initiateDisconnect, worker, &Worker::onInitiateDisconnect);
    connect(this, &Device::sendMessage, worker, &Worker::onSendMessage);
    connect(worker, &Worker::finalizeDisconnect, this, &Device::onFinalizeDisconnect);
    connect(worker, &Worker::finalizeConnect, this, &Device::onFinalizeConnect);


    worker_thread.start();
}

Device::~Device() {
    worker_thread.quit();
    worker_thread.wait();
}

void Device::onSendMessage(QByteArray message) {
    //qDebug() << "sendMessage";
    emit sendMessage(message);
}

void Device::onInitiateDisconnect() {
    emit initiateDisconnect();
}

void Device::onInitiateConnect(QBluetoothDeviceInfo device_info) {
    emit initiateConnect(device_info);
}

void Device::onFinalizeConnect() {
    emit finalizeConnect();
}

void Device::onFinalizeDisconnect() {
    emit finalizeDisconnect();
}