#include "soundcore/DeviceScanner.hpp"
#include "soundcore/DeviceList.hpp"
#include <QDebug>

DeviceScanner::DeviceScanner(DeviceList& device_list) : device_list{device_list}{
    connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &DeviceScanner::onDeviceDiscovered);
}

void DeviceScanner::run (){
    device_discovery_agent.start(QBluetoothDeviceDiscoveryAgent::supportedDiscoveryMethods());
}

void DeviceScanner::onDeviceDiscovered(QBluetoothDeviceInfo device_info) {
        device_list.push(device_info);
}

void DeviceScanner::startScan(){
    start();
}
void DeviceScanner::stopScan(){
    device_discovery_agent.stop();
    exit();
}
bool DeviceScanner::isScanning(){
    return isRunning();
}