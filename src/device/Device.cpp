#include <soundcore/device/Device.hpp>

Device::Device(QObject *parent) : QObject(parent) {
    QObject::connect(&m_service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                     [this](QBluetoothServiceInfo service_info) {
                         if (service_info.serviceName() == "Serial Port Profile") {
                             m_socket.setSocketDescriptor(m_socket.socketDescriptor(),
                                                          QBluetoothServiceInfo::RfcommProtocol);
                             m_socket.connectToService(service_info);
                         }
                     });
    connect(&m_socket, &QBluetoothSocket::connected, this, &Device::onConnectedSocket);
    connect(&m_socket, &QBluetoothSocket::disconnected, this, &Device::onDisconnectedSocket);
}

void Device::onInitiateConnect(QBluetoothDeviceInfo device_info) {
    m_service_discovery_agent.clear();
    m_service_discovery_agent.setRemoteAddress(device_info.address());
    m_service_discovery_agent.start();
}

void Device::onInitiateDisconnect() {
    m_socket.disconnectFromService();
}

void Device::onSendMessage(QByteArray message) {
    m_socket.write(message);
}

void Device::onConnectedSocket() {
    m_service_discovery_agent.stop();
    emit finalizeConnect();
}

void Device::onDisconnectedSocket() {
    emit finalizeDisconnect();
}
