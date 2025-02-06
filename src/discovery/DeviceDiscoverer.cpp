#include "soundcore/discovery/DeviceDiscoverer.hpp"

DeviceDiscoverer::State DeviceDiscoverer::state() {
    return m_state;
}

void DeviceDiscoverer::start() {
    if(m_device_discovery_agent.isActive())
    {
        m_device_discovery_agent.stop();
    }
    emit resetDiscoveredDevices();
    m_state = State::Discovering;
    m_device_discovery_agent.start();
    emit stateChanged(m_state);
    qDebug() << "DeviceDiscoverer::start() called";
}

void DeviceDiscoverer::stop() {
    m_state = State::Idle;
    m_device_discovery_agent.stop();
    emit stateChanged(m_state);
    qDebug() << "DeviceDiscoverer::stop() called";
}

DeviceDiscoverer::DeviceDiscoverer(QObject *parent) {
    connect(&m_device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
            &DeviceDiscoverer::onDeviceDiscovered);
}

void DeviceDiscoverer::onDeviceDiscovered(QBluetoothDeviceInfo device_info) {
    qDebug() << "Discovered Device";
    emit deviceDiscovered(device_info);
}