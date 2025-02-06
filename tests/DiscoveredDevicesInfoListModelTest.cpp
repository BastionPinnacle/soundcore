#include <QtTest>
#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"


class DiscoveredDevicesInfoListModelTest : public QObject {
Q_OBJECT

private slots:

    void testOnStateChangedWithCanConnectBehaviour();

    void testAddingItem();

    void testResetDiscoveredDevices();

    void testQAbstractListModel();

    void testChoosingCurrentItemInIdleState();

    void testChoosingCurrentItemInDiscoveringState();

};


void DiscoveredDevicesInfoListModelTest::testOnStateChangedWithCanConnectBehaviour() {
    DiscoveredDevicesInfoListModel device_info_list;
    QSignalSpy can_connect_changed_spy(&device_info_list, &DiscoveredDevicesInfoListModel::canConnectChanged);
    QVERIFY(can_connect_changed_spy.count() == 0);
    device_info_list.onStateChanged(DeviceDiscoverer::State::Discovering);
    can_connect_changed_spy.wait(100);
    QVERIFY(can_connect_changed_spy.count() == 1);
    device_info_list.onStateChanged(DeviceDiscoverer::State::Idle);
    can_connect_changed_spy.wait(100);
    QVERIFY(can_connect_changed_spy.count() == 2);
}

void DiscoveredDevicesInfoListModelTest::testAddingItem() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QVERIFY(device_info_list.rowCount() == 0);
    device_info_list.onDeviceDiscovered(device_info);
    QVERIFY(device_info_list.rowCount() == 1);
    device_info_list.onDeviceDiscovered(device_info);
    QVERIFY(device_info_list.rowCount() == 1);
    device_info.setName("Changed name");
    device_info_list.onDeviceDiscovered(device_info);
    QVERIFY(device_info_list.rowCount() == 2);
}

void DiscoveredDevicesInfoListModelTest::testResetDiscoveredDevices() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    device_info_list.onDeviceDiscovered(device_info);
    QVERIFY(device_info_list.rowCount() == 1);
    device_info_list.onResetDiscoveredDevices();
    QVERIFY(device_info_list.rowCount() == 0);
}

void DiscoveredDevicesInfoListModelTest::testQAbstractListModel() {
    DiscoveredDevicesInfoListModel device_info_list;
    QAbstractItemModelTester tester(&device_info_list);
}

void DiscoveredDevicesInfoListModelTest::testChoosingCurrentItemInDiscoveringState() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QSignalSpy connect_device_spy(&device_info_list, &DiscoveredDevicesInfoListModel::connectDevice);
    device_info_list.onStateChanged(DeviceDiscoverer::State::Discovering);
    device_info_list.onDeviceDiscovered(device_info);
    device_info_list.connectDeviceOnCurrentIndex(0);
    connect_device_spy.wait(100);
    QVERIFY(connect_device_spy.count() == 0);
}

void DiscoveredDevicesInfoListModelTest::testChoosingCurrentItemInIdleState() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QSignalSpy connect_device_spy(&device_info_list, &DiscoveredDevicesInfoListModel::connectDevice);
    device_info_list.onDeviceDiscovered(device_info);
    device_info_list.onStateChanged(DeviceDiscoverer::State::Idle);
    device_info_list.connectDeviceOnCurrentIndex(0);
    connect_device_spy.wait(100);
    QVERIFY(connect_device_spy.count() == 1);
}

QTEST_MAIN(DiscoveredDevicesInfoListModelTest)

#include "DiscoveredDevicesInfoListModelTest.moc"