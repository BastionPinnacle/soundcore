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
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = DeviceRoles::NameRole) const override;
    void connectDeviceOnCurrentIndex(int index);
    Q_PROPERTY(bool can_connect MEMBER m_can_connect READ canConnect NOTIFY canConnectChanged)
    bool canConnect() const;
    signals:
    void connectDevice(QBluetoothDeviceInfo device_info);
    void canConnectChanged(bool can_connect);
protected:
    QHash<int, QByteArray> roleNames() const override;
public slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device);
    void onResetDiscoveredDevices();
    void onStateChanged(DeviceDiscoverer::State state);
private:
    QList<QBluetoothDeviceInfo>  m_devices_list;
    bool m_can_connect = true;
};