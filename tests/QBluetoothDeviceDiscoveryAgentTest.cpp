#include <QtTest/QtTest>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QSignalSpy>
#include "soundcore/DeviceList.hpp"

class TestBluetoothDiscovery : public QObject {
Q_OBJECT

private slots:
    void testDeviceDiscovery();
    void testStatesInDeviceList();
    void testOnDeviceDiscoveryInDeviceList();
};

void TestBluetoothDiscovery::testDeviceDiscovery() {
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    device_discovery_agent.setLowEnergyDiscoveryTimeout(500);
    QBluetoothServiceDiscoveryAgent service_discovery_agent;
    QBluetoothSocket bluetooth_socket;

    connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            [&service_discovery_agent](QBluetoothDeviceInfo device) {
                if (device.name().contains("soundcore", Qt::CaseInsensitive)) {
                    service_discovery_agent.setRemoteAddress(device.address());
                    qDebug() << "Soundcore device found";
                    service_discovery_agent.start();
                } else {
                    qDebug() << "Soundcore device not found";
                }
            });
    connect(&service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
            [&bluetooth_socket](QBluetoothServiceInfo service_info) {
                if (service_info.serviceName() == "Serial Port Profile") {
                    bluetooth_socket.setSocketDescriptor(bluetooth_socket.socketDescriptor(),
                                                         service_info.socketProtocol(), bluetooth_socket.state(),
                                                         bluetooth_socket.openMode());
                    bluetooth_socket.connectToService(service_info);
                }
            });
    connect(&bluetooth_socket, &QBluetoothSocket::connected, [&bluetooth_socket]() {
        qDebug() << "CONNECTED";
        bluetooth_socket.write(QByteArray::fromHex("08ee000000028114000200a0968278787878789f"));
        qDebug() << bluetooth_socket.readAll();
    });

    QSignalSpy device_discovered_spy(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered);
    QSignalSpy device_discovery_finished_spy(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::finished);
    QSignalSpy service_discovered_spy(&service_discovery_agent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered);


    QVERIFY(device_discovered_spy.isValid());
    QVERIFY(device_discovery_finished_spy.isValid());
    QVERIFY(service_discovered_spy.isValid());

    device_discovery_agent.start();
    device_discovery_finished_spy.wait(10000);

    QVERIFY(device_discovered_spy.count() > 0);
    QVERIFY(device_discovery_finished_spy.count() > 0);
    QVERIFY(service_discovered_spy.count() > 0);
}

void TestBluetoothDiscovery::testStatesInDeviceList() {
    DeviceList device_list;
    QVERIFY(device_list.getState()==DeviceList::State::Initialized);
    device_list.refresh();
    QVERIFY(device_list.getState()==DeviceList::State::Refreshing);
    device_list.stopRefreshing();
    QVERIFY(device_list.getState()==DeviceList::State::Refreshed);
    device_list.refresh();
    QVERIFY(device_list.getState()==DeviceList::State::Refreshing);
}

void TestBluetoothDiscovery::testOnDeviceDiscoveryInDeviceList() {
    DeviceList device_list;
    device_list.refresh();
    sleep(1);
    device_list.stopRefreshing();
    QVERIFY(device_list.numberOfDevices()>0);
}

QTEST_MAIN(TestBluetoothDiscovery)

#include "QBluetoothDeviceDiscoveryAgentTest.moc"
