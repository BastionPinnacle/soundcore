#include "soundcore/Device.hpp"

#include "soundcore/DeviceInfoList.hpp"

#include <QtTest>


class DeviceTest : public QObject {
Q_OBJECT
private slots:
    void initTestCase()
    {
        device_info_list.refresh();
        device_info_list.stopRefreshing();
        Q_ASSERT(device_info_list.numberOfDevices()==1);
    }
    void tryConnectingToAndDisconnectingFromExistingAddress();
    void tryConnectingToAddressFromDefaultDevice();

private:
    DeviceInfoList device_info_list;
};

void DeviceTest::tryConnectingToAndDisconnectingFromExistingAddress() {
    auto device_info = device_info_list.getDeviceInfoAt(0);
    Device device(device_info);
    QSignalSpy device_connected_spy(&device, &Device::connected);
    QVERIFY(device_connected_spy.isValid());
    device.tryToConnect();
    device_connected_spy.wait(500);
    QVERIFY(device_connected_spy.count()==1);
    QSignalSpy device_disconnected_spy(&device, &Device::disconnected);
    QVERIFY(device_disconnected_spy.isValid());
    device.tryToDisconnect();
    device_disconnected_spy.wait(500);
    QVERIFY(device_disconnected_spy.count()==1);
 }

void DeviceTest::tryConnectingToAddressFromDefaultDevice() {
    auto device_info = QBluetoothDeviceInfo{};
    Device device(device_info);
    QSignalSpy device_connected_spy(&device, &Device::connected);
    QVERIFY(device_connected_spy.isValid());
    device.tryToConnect();
    device_connected_spy.wait(500);
    QVERIFY(device_connected_spy.count()==0);
}

QTEST_MAIN(DeviceTest)

#include "DeviceTest.moc"