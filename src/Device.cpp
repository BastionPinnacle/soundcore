#include <soundcore/Device.hpp>

Device::Device(const QBluetoothDeviceInfo &device_info) : device_info{device_info}
{
}

Device::Device(const Device &device) : device_info{device.device_info}
{
}

QBluetoothDeviceInfo Device::getDeviceInfo()
{
    return device_info;
}

QBluetoothSocket* Device::createSocket()
{
    auto socket = new QBluetoothSocket(QBluetoothServiceInfo::Protocol::RfcommProtocol);
    socket->connectToService(device_info.address(),device_info.serviceUuids()[0], QBluetoothSocket::ReadWrite);
    return socket;
}