#include <QObject>
#include <QBluetoothDeviceInfo>
#include <iostream>
#include <mutex>
#include "soundcore/DeviceInfoList.hpp"


DeviceInfoList::DeviceInfoList(QObject *parent)
        : QAbstractListModel(parent) {
    connect(&device_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceInfoList::onDeviceDiscovered);
}

DeviceInfoList::State DeviceInfoList::state() const {
    return m_state;
}

void DeviceInfoList::refresh() {
    qDebug() << "Refresh called";
    if(state()!=State::Refreshing)
    {
        resetDevices();
        m_state = State::Refreshing;
        stateChanged(m_state);
        device_discovery_agent.start();
    }
}

void DeviceInfoList::stopRefreshing() {
    qDebug() << "Stop refreshing called";
    if(state()==State::Refreshing)
    {
        m_state = State::Refreshed;
        stateChanged(m_state);
        device_discovery_agent.stop();
    }
}

void DeviceInfoList::onDeviceDiscovered(QBluetoothDeviceInfo device) {
    if (!devices.contains(device)) {
        int row = devices.size();
        beginInsertRows(QModelIndex(), row, row);

        devices.append(device);

        endInsertRows();

        qDebug() << "onDeviceDiscovered, devices size: " << devices.size();
    }
}

std::size_t DeviceInfoList::numberOfDevices()
{
    return devices.size();
}


int DeviceInfoList::rowCount(const QModelIndex &parent) const {
    return devices.count();
}

QVariant DeviceInfoList::data(const QModelIndex &index, int role) const {
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

QHash<int, QByteArray> DeviceInfoList::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AddressRole] = "address";
    return roles;
}

void DeviceInfoList::resetDevices() {
    beginResetModel();
    devices.clear();
    endResetModel();
}

QBluetoothDeviceInfo DeviceInfoList::getDeviceInfoAt(int index) const {
    if(0 <= index  && index < devices.size())
    {
        return devices[index];
    }
    return QBluetoothDeviceInfo{};
}