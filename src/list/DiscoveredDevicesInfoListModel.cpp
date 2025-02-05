#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"

#include <QBluetoothAddress>

void DiscoveredDevicesInfoListModel::onDeviceDiscovered(QBluetoothDeviceInfo device) {
    if (!devices.contains(device)) {
        int row = devices.size();
        beginInsertRows(QModelIndex(), row, row);
        devices.append(device);
        endInsertRows();
    }
}

int DiscoveredDevicesInfoListModel::rowCount(const QModelIndex &parent) const {
    return devices.count();
}

QVariant DiscoveredDevicesInfoListModel::data(const QModelIndex &index, int role) const {
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

QHash<int, QByteArray> DiscoveredDevicesInfoListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AddressRole] = "address";
    return roles;
}


void DiscoveredDevicesInfoListModel::connectDeviceOnCurrentIndex(int index)
{
    if(0<=index && index < devices.count())
    {
        auto device_info = devices[index];
        emit connectDevice(device_info);
    }
}

void DiscoveredDevicesInfoListModel::onResetDiscoveredDevices(){
    beginResetModel();
    devices.clear();
    endResetModel();
}
