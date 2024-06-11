#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
class DeviceScanner : public QObject {
    Q_OBJECT
public:
    DeviceScanner(){
        connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                this, &DeviceScanner::onDeviceDiscovered);
    }
    void scanForDevices() {
        state = State::Scanning;
        device_discovery_agent.start(QBluetoothDeviceDiscoveryAgent::supportedDiscoveryMethods());
    }
    void endScanningForDevices(){
        state = State::Scanning;
        device_discovery_agent.stop();
    }
    enum class State : uint8_t {
        Idle = 0,
        Scanning = 1
    };
public slots:
            void onDeviceDiscovered(QBluetoothDeviceInfo device_info) {
        emit deviceDiscovered(device_info);
    }
    signals:
            void deviceDiscovered(QBluetoothDeviceInfo device_info);

private:
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    State state;
};