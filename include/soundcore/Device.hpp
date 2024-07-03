#pragma once

#include <QObject>
#include <QBluetoothDeviceInfo>
#include <QBluetoothSocket>

class Device : public QObject {
Q_OBJECT

public:
    Device() = delete;
    Device(const QBluetoothDeviceInfo& device_info);
    Device(const Device& device);

    QBluetoothSocket* createSocket();
    QBluetoothDeviceInfo getDeviceInfo();
private:
    QBluetoothDeviceInfo device_info;
};
