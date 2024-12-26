#include <soundcore/Device.hpp>

Device::Device(const QBluetoothDeviceInfo &device_info) : device_info{device_info}
{
}

QString Device::name() const
{
    return device_info.name();
}

bool Device::status() const
{
    return socket;
}

bool Device::connect()
{
    disconnect();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::Protocol::RfcommProtocol);
    socket->connectToService(device_info.address(),device_info.serviceUuids()[0], QBluetoothSocket::ReadWrite);
    if(socket && socket->canReadLine())
    {
       return true;
    }
    return false;
}

void Device::disconnect()
{
    if(socket)
    {
        socket->disconnectFromService();
        delete socket;
    }
}