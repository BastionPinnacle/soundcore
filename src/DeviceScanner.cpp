#include "soundcore/DeviceScanner.hpp"
#include "soundcore/DeviceList.hpp"
#include <QDebug>

DeviceScanner::DeviceScanner(DeviceList& device_list) : device_list{device_list}{
    connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &DeviceScanner::onDeviceDiscovered);
}

void DeviceScanner::startScan() {
    if (state == State::Scanning) {
        qDebug() << "Is already scanning.";
        return;
    }
    scanning_thread = std::jthread(&DeviceScanner::startScanningForDevices, this, stop_source.get_token());
}

void DeviceScanner::startScanningForDevices(std::stop_token stop_token) {
    state = State::Scanning;
    device_discovery_agent.start(QBluetoothDeviceDiscoveryAgent::supportedDiscoveryMethods());
    while(!stop_token.stop_requested())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    device_discovery_agent.stop();
    state = State::Idle;
}

void DeviceScanner::stopScan(){
    stop_source.request_stop();
}

bool DeviceScanner::isScanning() {
    return state == State::Scanning;
}

void DeviceScanner::onDeviceDiscovered(QBluetoothDeviceInfo device_info) {
        device_list.push(device_info);
}