#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QDirIterator>
#include "include/soundcore/DeviceScanner.hpp"
#include "include/soundcore/DeviceList.hpp"
#include "include/soundcore/Device.hpp"
#include <QTimer>

/*

class DeviceDiscoverer : public QObject {
    QBluetoothSocket *qBluetoothSocket;
public:
    void startDeviceDiscovery() {
        QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
        connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                this, &DeviceDiscoverer::deviceDiscovered);
        discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::supportedDiscoveryMethods());
    }

public slots:

    void deviceDiscovered(QBluetoothDeviceInfo device) {
        qDebug() << device.name();
        QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
        qBluetoothSocket = new QBluetoothSocket(QBluetoothServiceInfo::Protocol::RfcommProtocol);
        connect(qBluetoothSocket, &QBluetoothSocket::connected,
                this, &DeviceDiscoverer::connected);
        connect(qBluetoothSocket, &QBluetoothSocket::errorOccurred,
                this, &DeviceDiscoverer::errorOccurred);
        qBluetoothSocket->connectToService(device.address(), device.serviceUuids()[0], QBluetoothSocket::WriteOnly);
    }

    void connected() {
        std::cout << "Current write channel: " << qBluetoothSocket->currentWriteChannel() << std::endl;
        std::cout << qBluetoothSocket->writeChannelCount();

        QByteArray hexString = "08ee000000028114000200a0968278787878789f";

        // Convert to QByteArray
        QByteArray byteArray = QByteArray::fromHex(hexString);

        // Output the byte array
        qDebug() << "Hex String:" << hexString;
        qDebug() << "Byte Array:" << byteArray;
        qBluetoothSocket->write(byteArray);
        qBluetoothSocket->disconnect();
    }

    void errorOccurred() {
        qDebug() << "Error occured";
    }

};

*/

int main(int argc, char **argv) {
    //qmlRegisterType<DeviceList>("soundcore", 1, 0, "DeviceList");
    //qmlRegisterType<DeviceList>("soundcore", 1, 0, "DeviceList");
    //QGuiApplication app (argc, argv);
    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    QCoreApplication app(argc, argv);
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
    qDebug() << device.serviceUuids().size();
    for(auto service : device.serviceUuids())
    {
        qDebug() << service;
    }
    QObject::connect(qBluetoothSocket, &QBluetoothSocket::connected, [qBluetoothSocket](){
        qDebug() << "CONNECTED!";
        QByteArray hexString = "08ee0000000281140013005a64828c8c82785a4c";
        QByteArray byteArray = QByteArray::fromHex(hexString);
        qDebug() << "Hex String:" << hexString;
        qDebug() << "Byte Array:" << byteArray;
        qBluetoothSocket->write(byteArray);
    });
    qBluetoothSocket->connectToService( device.serviceUuids()[0]);
    return app.exec ();
}