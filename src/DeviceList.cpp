#include <QObject>
#include <QBluetoothDeviceInfo>
#include <iostream>
#include <mutex>
#include "soundcore/DeviceList.hpp"
#include "soundcore/DeviceScanner.hpp"

DeviceList::DeviceList(): device_scanner{*this}{}

void DeviceList::refresh() {
    if (!device_scanner.isScanning()) device_scanner.startScan();
}

void DeviceList::stopRefreshing() {
    if (device_scanner.isScanning()) device_scanner.stopScan();
}

void DeviceList::push(QBluetoothDeviceInfo device_info) {
    if (std::find(devices.begin(), devices.end(), device_info) != devices.end()) {
        devices.emplace_back(device_info);
    }
}

std::vector<QBluetoothDeviceInfo> &DeviceList::getDevices() {
    return devices;
}