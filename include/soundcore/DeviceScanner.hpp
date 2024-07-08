#pragma once
#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <stop_token>
#include <thread>

class DeviceList;

class DeviceScanner : public QObject {
    Q_OBJECT
public:
    DeviceScanner(DeviceList& device_list);
    Q_INVOKABLE void startScan();
    Q_INVOKABLE void stopScan();
    Q_INVOKABLE bool isScanning();

    enum class State : uint8_t {
        Idle = 0,
        Scanning = 1
    };

public slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device_info);
private:
    void startScanningForDevices(std::stop_token stopToken);
    DeviceList& device_list;
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    std::jthread scanning_thread;
    std::stop_source stop_source;
    std::atomic<State> state = State::Idle;
};