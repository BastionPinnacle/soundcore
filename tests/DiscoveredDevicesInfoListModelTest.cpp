#include <QtTest>
#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"


class DiscoveredDevicesInfoListModelTest : public QObject {
    Q_OBJECT

private slots:
    void testQAbstractListModel();
    void testAddingItem();
    void testChoosingCurrentItem();
};


void DiscoveredDevicesInfoListModelTest::testQAbstractListModel() {
    DiscoveredDevicesInfoListModel device_info_list;
    QAbstractItemModelTester tester(&device_info_list);
}

void DiscoveredDevicesInfoListModelTest::testAddingItem() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QVERIFY(device_info_list.rowCount()==0);
    device_info_list.onDeviceDiscovered(device_info);
    QVERIFY(device_info_list.rowCount()==1);
    device_info_list.onResetDiscoveredDevices();
    QVERIFY(device_info_list.rowCount()==0);
}


void DiscoveredDevicesInfoListModelTest::testChoosingCurrentItem() {
    DiscoveredDevicesInfoListModel device_info_list;
    QBluetoothDeviceInfo device_info;
    QSignalSpy connect_device_spy(&device_info_list, &DiscoveredDevicesInfoListModel::connectDevice);
    device_info_list.onDeviceDiscovered(device_info);
    device_info_list.connectDeviceOnCurrentIndex(0);
    connect_device_spy.wait(100);
    QVERIFY(connect_device_spy.count()==1);
}

QTEST_MAIN(DiscoveredDevicesInfoListModelTest)

#include "DiscoveredDevicesInfoListModelTest.moc"