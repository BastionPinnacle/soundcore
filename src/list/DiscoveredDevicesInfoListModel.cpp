#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"
#include "soundcore/discovery/DeviceDiscoverer.hpp"

#include <QBluetoothAddress>

void DiscoveredDevicesInfoListModel::onDeviceDiscovered(QBluetoothDeviceInfo device) {
    if (!m_devices_list.contains(device)) {
        int row = m_devices_list.size();
        beginInsertRows(QModelIndex(), row, row);
        m_devices_list.append(device);
        endInsertRows();
    }
}

int DiscoveredDevicesInfoListModel::rowCount(const QModelIndex &parent) const {
    return m_devices_list.count();
}

QVariant DiscoveredDevicesInfoListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_devices_list.count())
        return {};
    const QBluetoothDeviceInfo &device_info = m_devices_list[index.row()];
    switch (role) {
        case NameRole:
            return device_info.name();
        case AddressRole:
            return device_info.address().toString();
        default:
            return {};
    }
}

QHash<int, QByteArray> DiscoveredDevicesInfoListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AddressRole] = "address";
    return roles;
}


void DiscoveredDevicesInfoListModel::connectDeviceOnCurrentIndex(int index)
{
    if(0<=index && index < m_devices_list.count())
    {
        auto device_info = m_devices_list[index];
        emit connectDevice(device_info);
    }
}

void DiscoveredDevicesInfoListModel::onResetDiscoveredDevices(){
    beginResetModel();
    m_devices_list.clear();
    endResetModel();
}

void DiscoveredDevicesInfoListModel::onStateChanged(DeviceDiscoverer::State state) {
    if(state == DeviceDiscoverer::State::Idle){
        m_can_connect = true;
        return;
    }
    m_can_connect = false;
}