#include <QObject>
#include <QBluetoothDeviceInfo>
#include <iostream>
#include <mutex>
#include "soundcore/DeviceList.hpp"


DeviceList::DeviceList(QObject *parent)
        : QAbstractListModel(parent) {
    connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceList::onDeviceDiscovered);
}

DeviceList::State DeviceList::getState() {
    return state;
}

void DeviceList::refresh() {
    qDebug() << "Refresh called";
    if(getState()!=State::Refreshing)
    {
        state = State::Refreshing;
        device_discovery_agent.start();
    }
}

void DeviceList::stopRefreshing() {
    qDebug() << "Stop refreshing called";
    if(getState()==State::Refreshing)
    {
        state = State::Refreshed;
        device_discovery_agent.stop();
    }
}

void DeviceList::onDeviceDiscovered(QBluetoothDeviceInfo device) {
    if(!devices.contains(device)) {
        beginInsertRows(QModelIndex(), devices.size(), devices.size()+1);
        devices.append(device);
        endInsertRows();
        qDebug() << "onDeviceDiscovered" << devices.size();
    }
}

std::size_t DeviceList::numberOfDevices()
{
    return devices.size();
}

int DeviceList::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return devices.size();
}

QVariant DeviceList::data(const QModelIndex &index, int role) const {
    qDebug() << "XDDD";
    if (index.row() < 0 || index.row() >= devices.count())
        return {};
    const QBluetoothDeviceInfo &device_info = devices[index.row()];
    switch (role) {
        case NameRole:
            return device_info.name();
        case AddressRole:
            return device_info.address().toString();
        default:
            return {};
    }
}

QHash<int, QByteArray> DeviceList::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AddressRole] = "address";
    return roles;
}