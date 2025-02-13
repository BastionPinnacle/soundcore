#pragma once
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>

#include "soundcore/discovery/DeviceDiscoverer.hpp"

class DiscoveredDevicesInfoListModel : public QAbstractListModel {
Q_OBJECT
public:
    enum DeviceRoles{
        NameRole = Qt::UserRole + 1,
        AddressRole
    };
    Q_PROPERTY(int count READ count NOTIFY countChanged);
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = DeviceRoles::NameRole) const override;
    int count();
    Q_INVOKABLE void connectDeviceOnCurrentIndex(int index);
    signals:
    void connectDevice(QBluetoothDeviceInfo device_info);
    void countChanged(int count);
protected:
    QHash<int, QByteArray> roleNames() const override;
public slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device);
    void onResetDiscoveredDevices();
private:
    QList<QBluetoothDeviceInfo>  m_devices_list;
};