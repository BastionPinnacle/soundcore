#pragma once
#include <QObject>
#include <QThread>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>

class DeviceList;

class DeviceScanner : public QThread {
    Q_OBJECT
    void run () override;
public:
    DeviceScanner(DeviceList& device_list);
    Q_INVOKABLE void startScan();
    Q_INVOKABLE void stopScan();
    Q_INVOKABLE bool isScanning();
public slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device_info);
private:
    DeviceList& device_list;
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
};