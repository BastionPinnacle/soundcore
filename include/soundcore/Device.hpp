#pragma once

#include <QObject>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>

class Device : public QObject {
Q_OBJECT

public:
    Device() {}

    Device(QBluetoothDeviceInfo device_info) : device_info(device_info) {}

    Device(const Device& device) : device_info(device.device_info){}

    QBluetoothSocket createSocket();

    QBluetoothDeviceInfo getDeviceInfo() const {
        return device_info;
    }

private:
    QBluetoothDeviceInfo device_info;
};
