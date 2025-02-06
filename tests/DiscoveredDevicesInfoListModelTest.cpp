#include <QtTest>
#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"


class DiscoveredDevicesInfoListModelTest : public QObject {
Q_OBJECT

private slots:

    void testAddingItem();

    void testResetDiscoveredDevices();

    void testQAbstractListModel();

    void testChoosingCurrentItem();

    void testGettingName();

};

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

void DiscoveredDevicesInfoListModelTest::testChoosingCurrentItem() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QSignalSpy connect_device_spy(&device_info_list, &DiscoveredDevicesInfoListModel::connectDevice);
    device_info_list.onDeviceDiscovered(device_info);
    device_info_list.connectDeviceOnCurrentIndex(0);
    connect_device_spy.wait(100);
    QVERIFY(connect_device_spy.count() == 1);
}


void DiscoveredDevicesInfoListModelTest::testGettingName() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QString custom_name{"Custom name"};
    device_info.setName(custom_name);
    device_info_list.onDeviceDiscovered(device_info);
    auto index = device_info_list.index(0, 0);
    auto element = device_info_list.data(index, DiscoveredDevicesInfoListModel::DeviceRoles::NameRole);
    QVERIFY(element.toString() == custom_name);
}

QTEST_MAIN(DiscoveredDevicesInfoListModelTest)

#include "DiscoveredDevicesInfoListModelTest.moc"