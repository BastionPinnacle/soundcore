#include <iostream>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QCoreApplication>
#include <QLoggingCategory>


class DeviceDiscoverer : public QObject{
    QBluetoothSocket* qBluetoothSocket;
public:
    void startDeviceDiscovery()
    {
        QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
        connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                this, &DeviceDiscoverer::deviceDiscovered);
        discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::supportedDiscoveryMethods());
    }
public slots:
    void deviceDiscovered(QBluetoothDeviceInfo device)
    {
        QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
        qBluetoothSocket = new QBluetoothSocket(QBluetoothServiceInfo::Protocol::RfcommProtocol);
        connect(qBluetoothSocket, &QBluetoothSocket::connected,
                this, &DeviceDiscoverer::connected);
        connect(qBluetoothSocket, &QBluetoothSocket::errorOccurred,
                this, &DeviceDiscoverer::errorOccurred);
        qBluetoothSocket->connectToService(device.address(),device.serviceUuids()[0], QBluetoothSocket::WriteOnly);
    }
    void connected(){
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
    void errorOccurred(){
        qDebug() << "Error occured";
    }

};




int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    DeviceDiscoverer deviceDiscoverer;
    deviceDiscoverer.startDeviceDiscovery();
    app.exec();
}