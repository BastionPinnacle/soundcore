#include <soundcore/Device.hpp>

Device::Device(const QBluetoothDeviceInfo &device_info, QObject *parent) : QObject(parent), device_info{device_info} {
    setup();
}

QString Device::name() const {
    return device_info.name();
}

void Device::tryToConnect() {
    service_discovery_agent.setRemoteAddress(device_info.address());
    service_discovery_agent.start();
}

void Device::tryToDisconnect() {
    socket->disconnectFromService();
}

void Device::setup() {
    QObject::connect(&service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                     [this](QBluetoothServiceInfo service_info) {
                         if (service_info.serviceName() == "Serial Port Profile") {
                             if (socket) {
                                 tryToDisconnect();
                             } else {
                                 socket = new QBluetoothSocket(service_info.socketProtocol());
                                 QObject::connect(socket, &QBluetoothSocket::connected, [this]() {
                                     service_discovery_agent.stop(); emit connected();
                                 });
                                 QObject::connect(socket, &QBluetoothSocket::disconnected,
                                                  [this]() {
                                                      delete socket;
                                                      socket = nullptr; emit disconnected();
                                                  });
                                 socket->connectToService(service_info);
                             }
                         }
                     });
}

Device::~Device(){
    if(socket)
    {
        socket->disconnectFromService();
    }
    delete socket;
}