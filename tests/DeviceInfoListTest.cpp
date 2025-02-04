#include "soundcore/DeviceInfoList.hpp"

#include <QtTest>


class DeviceInfoListTest : public QObject {
Q_OBJECT

private slots:
    void shouldProperlyChangeStates();
    void shouldTestQAbstractListModel();
    void shouldReturnMeaningfulValueNotDefault();
    void shouldReturnDefaultValue();
};


void DeviceInfoListTest::shouldProperlyChangeStates() {
    DeviceInfoList device_info_list;
    QSignalSpy state_changed_signal_spy(&device_info_list, &DeviceInfoList::stateChanged);
    QVERIFY(state_changed_signal_spy.isValid());
    QVERIFY(state_changed_signal_spy.count()==0);
    Q_ASSERT(device_info_list.state()==DeviceInfoList::State::Initialized);
    device_info_list.refresh();
    QVERIFY(state_changed_signal_spy.count()==1);
    Q_ASSERT(device_info_list.state()==DeviceInfoList::State::Refreshing);
    device_info_list.stopRefreshing();
    QVERIFY(state_changed_signal_spy.count()==2);
    Q_ASSERT(device_info_list.state()==DeviceInfoList::State::Refreshed);
    device_info_list.refresh();
    QVERIFY(state_changed_signal_spy.count()==3);
    Q_ASSERT(device_info_list.state()==DeviceInfoList::State::Refreshing);
}

void DeviceInfoListTest::shouldReturnMeaningfulValueNotDefault() {
    DeviceInfoList device_info_list;
    device_info_list.refresh();
    device_info_list.stopRefreshing();
    if(device_info_list.numberOfDevices()>0)
    {
        auto device_info = device_info_list.getDeviceInfoAt(0);
        QVERIFY(device_info!=QBluetoothDeviceInfo{});
    }
}

void DeviceInfoListTest::shouldReturnDefaultValue() {
    DeviceInfoList device_info_list;
    auto device_info = device_info_list.getDeviceInfoAt(0);
    QVERIFY(device_info==QBluetoothDeviceInfo{});
}

void DeviceInfoListTest::shouldTestQAbstractListModel() {
    DeviceInfoList device_info_list;
    QAbstractItemModelTester tester(&device_info_list);
}

QTEST_MAIN(DeviceInfoListTest)

#include "DeviceInfoListTest.moc"