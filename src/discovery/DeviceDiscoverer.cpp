#include "soundcore/discovery/DeviceDiscoverer.hpp"


DeviceDiscoverer::State DeviceDiscoverer::state(){
    return m_state;
}
void DeviceDiscoverer::start(){
    m_state = State::Discovering;
    device_discovery_agent.start();
}

void DeviceDiscoverer::stop(){
    m_state = State::Idle;
    device_discovery_agent.stop();
}

void DeviceDiscoverer::onDeviceDiscovered(QBluetoothDeviceInfo device_info){
    emit deviceDiscovered(device_info);
}