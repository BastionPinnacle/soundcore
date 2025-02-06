#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"
#include "soundcore/discovery/DeviceDiscoverer.hpp"

#include <QBluetoothAddress>

void DiscoveredDevicesInfoListModel::onDeviceDiscovered(QBluetoothDeviceInfo device) {
    if (!m_devices_list.contains(device)) {
        beginInsertRows(QModelIndex(), m_devices_list.size(), m_devices_list.size());
        m_devices_list.append(device);
        qDebug() << m_devices_list.size();
        endInsertRows();
    }
}

int DiscoveredDevicesInfoListModel::rowCount(const QModelIndex &parent) const {
    return m_devices_list.size();
}

QVariant DiscoveredDevicesInfoListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return {};
    }
    auto item = m_devices_list.at(index.row());
    switch (role) {
        case NameRole:
            return QVariant(item.name());
        case AddressRole:
            return QVariant(item.address().toString());
    }
    return {};
}

QHash<int, QByteArray> DiscoveredDevicesInfoListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AddressRole] = "address";
    return roles;
}


void DiscoveredDevicesInfoListModel::connectDeviceOnCurrentIndex(int index)
{
    if(m_can_connect && 0<=index && index < m_devices_list.size())
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
    m_can_connect = (state == DeviceDiscoverer::State::Idle) ? true : false;
    emit canConnectChanged(m_can_connect);
}

bool DiscoveredDevicesInfoListModel::canConnect() const {
    return m_can_connect;
}