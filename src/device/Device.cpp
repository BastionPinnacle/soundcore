#include <soundcore/device/Device.hpp>

Device::Device(QObject* parent) : QObject(parent){
    setup();
}

void Device::onInitiateConnect(QBluetoothDeviceInfo device_info){
    m_service_discovery_agent.setRemoteAddress(device_info.address());
    m_service_discovery_agent.start();
}

void Device::onInitiateDisconnect() {
    m_socket->disconnectFromService();
}

void Device::setup() {
    QObject::connect(&m_service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                     [this](QBluetoothServiceInfo service_info) {
                         if (service_info.serviceName() == "Serial Port Profile") {
                             if (m_socket) {
                                 onInitiateDisconnect();
                             } else {
                                 m_socket = new QBluetoothSocket(service_info.socketProtocol());
                                 QObject::connect(m_socket, &QBluetoothSocket::connected, [this]() {
                                     m_service_discovery_agent.stop(); emit finalizeConnect();
                                 });
                                 QObject::connect(m_socket, &QBluetoothSocket::disconnected,
                                                  [this]() {
                                                      delete m_socket;
                                                      m_socket = nullptr; emit finalizeDisconnect();
                                                  });
                                 m_socket->connectToService(service_info);
                             }
                         }
                     });
}

void Device::onSendMessage(QByteArray message) {
    m_socket->write(message);
}