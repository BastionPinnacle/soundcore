#pragma once
#include <QObject>
#include <QBluetoothDeviceInfo>
#include <iostream>
#include <mutex>
#include "soundcore/DeviceScanner.hpp"

class DeviceList : public QObject {
    Q_OBJECT
public:
    DeviceList();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void stopRefreshing();
    void push(QBluetoothDeviceInfo device_info);
    std::vector<QBluetoothDeviceInfo>& getDevices();
private:
    std::vector<QBluetoothDeviceInfo> devices;
    DeviceScanner device_scanner;
};