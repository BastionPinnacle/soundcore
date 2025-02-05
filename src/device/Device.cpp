#include <soundcore/device/Device.hpp>

Device::Device(QObject* parent) : QObject(parent){
    setup();
}

void Device::onInitiateConnect(QBluetoothDeviceInfo device_info){
    service_discovery_agent.setRemoteAddress(device_info.address());
    service_discovery_agent.start();
}

void Device::onInitateDisconnect() {
    socket->disconnectFromService();
}

void Device::setup() {
    QObject::connect(&service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                     [this](QBluetoothServiceInfo service_info) {
                         if (service_info.serviceName() == "Serial Port Profile") {
                             if (socket) {
                                 onInitateDisconnect();
                             } else {
                                 socket = new QBluetoothSocket(service_info.socketProtocol());
                                 QObject::connect(socket, &QBluetoothSocket::connected, [this]() {
                                     service_discovery_agent.stop(); emit finalizeConnect();
                                 });
                                 QObject::connect(socket, &QBluetoothSocket::disconnected,
                                                  [this]() {
                                                      delete socket;
                                                      socket = nullptr; emit finalizeDisconnect();
                                                  });
                                 socket->connectToService(service_info);
                             }
                         }
                     });
}

void Device::onSendMessage(QByteArray message) {
    socket->write(message);
}