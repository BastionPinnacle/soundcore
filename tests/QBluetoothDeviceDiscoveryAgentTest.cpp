#include <QtTest/QtTest>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QSignalSpy>

class TestBluetoothDiscovery : public QObject {
Q_OBJECT

private slots:

    void testDeviceDiscovery();
};

void TestBluetoothDiscovery::testDeviceDiscovery() {
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    device_discovery_agent.setLowEnergyDiscoveryTimeout(5000);
    QBluetoothServiceDiscoveryAgent service_discovery_agent;
    QBluetoothSocket bluetooth_socket;

    connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            [&service_discovery_agent](QBluetoothDeviceInfo device) {
                qDebug() << device.name();
                service_discovery_agent.setRemoteAddress(device.address());
                service_discovery_agent.start();
            });
    connect(&service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
            [&bluetooth_socket](QBluetoothServiceInfo service_info) {
        if(service_info.serviceName() == "Serial Port Profile")
        {
            bluetooth_socket.setSocketDescriptor(bluetooth_socket.socketDescriptor(),service_info.socketProtocol(), bluetooth_socket.state(), bluetooth_socket.openMode());
            bluetooth_socket.connectToService(service_info);
        }
    });
    connect(&bluetooth_socket, &QBluetoothSocket::connected, [](){qDebug() << "CONNECTED"; });


    // Use QSignalSpy to track signals
    QSignalSpy device_discovered_spy(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered);
    QSignalSpy device_discovery_finished_spy(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::finished);
    QSignalSpy service_discovered_spy(&service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered);



    QVERIFY(device_discovered_spy.isValid());
    QVERIFY(device_discovery_finished_spy.isValid());
    QVERIFY(service_discovered_spy.isValid());
    // Start discovery
    device_discovery_agent.start();

    // Run the event loop and wait for signals (timeout after 10s)
    QVERIFY(device_discovery_finished_spy.wait(10000));

    // Ensure that at least one device was discovered (if expected)
    if (!device_discovered_spy.isEmpty()) {
        qDebug() << "Devices found:" << device_discovered_spy.count();
    } else {
        qDebug() << "No devices found (ensure Bluetooth is enabled)";
    }

    QVERIFY(device_discovery_finished_spy.count() > 0);  // Ensure finished() was emitted
}

QTEST_MAIN(TestBluetoothDiscovery)

#include "QBluetoothDeviceDiscoveryAgentTest.moc"
