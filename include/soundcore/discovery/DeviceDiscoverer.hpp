#pragma once

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>

class DeviceDiscoverer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state MEMBER m_state READ state NOTIFY stateChanged)
public:
    enum State{
        Idle,
        Discovering
    };
    Q_ENUM(State);
    State state();
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    signals:
    void deviceDiscovered(QBluetoothDeviceInfo device_info);
    void stateChanged(State state);
    void resetDiscoveredDevices();
private slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device_info);
private:
    QBluetoothDeviceDiscoveryAgent m_device_discovery_agent;
    State m_state = State::Idle;
};