#pragma once
#include <QObject>
#include <QBluetoothDeviceInfo>

#include "soundcore/Device.hpp"
#include <iostream>
#include <mutex>

class DeviceScanner;

class DeviceList : public QObject {
    Q_OBJECT
public:
    DeviceList();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void stopRefreshing();
    Q_INVOKABLE void filter();

    void push(QBluetoothDeviceInfo device_info);
    std::vector<Device>& getDevices();
private:
    std::mutex mtx;
    std::vector<Device> devices;
    std::unique_ptr<DeviceScanner> device_scanner;
};