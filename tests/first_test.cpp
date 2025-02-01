#include <gtest/gtest.h>
#include "soundcore/DeviceScanner.hpp"
#include "soundcore/DeviceList.hpp"
#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>
#include <QBluetoothSocket>
#include <latch>


TEST(QBluetoothDeviceDiscoveryAgentTest, TestBehavior) {
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    QList<QBluetoothDeviceInfo> device_list;
    auto qBluetoothSocket = new QBluetoothSocket(QBluetoothServiceInfo::Protocol::RfcommProtocol);
    QObject::connect(&device_discovery_agent,
                     &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                     [&device_list](const QBluetoothDeviceInfo &device) {
                         qDebug() << "Discovered device:" << device.name() << device.address().toString()
                                  << device.serviceUuids().size();
                         device_list.append(device);
                     });
    device_discovery_agent.start(QBluetoothDeviceDiscoveryAgent::supportedDiscoveryMethods());
    device_discovery_agent.stop();
    qDebug() << device_list.size();
    auto device = device_list.at(0);
    qBluetoothSocket->connectToService(device.address(),device.serviceUuids().at(0));

}


TEST(DeviceListTest, TestScanning) {
    DeviceList device_list;
    device_list.refresh();
    std::this_thread::sleep_for(std::chrono::seconds{1});
    device_list.stopRefreshing();
    auto devices = device_list.getDevices();

    ASSERT_NE(devices.size(), 0);
}
