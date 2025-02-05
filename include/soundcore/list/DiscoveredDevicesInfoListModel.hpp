#pragma once
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>

class DiscoveredDevicesInfoListModel : public QAbstractListModel {
Q_OBJECT
public:
    enum DeviceRoles{
        NameRole = Qt::UserRole + 1,
        AddressRole
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = DeviceRoles::NameRole) const override;
    Q_INVOKABLE void connectDeviceOnCurrentIndex(int index);
    signals:
    void connectDevice(QBluetoothDeviceInfo device_info);
protected:
    QHash<int, QByteArray> roleNames() const override;
private slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device);
    void onResetDiscoveredDevices();
private:
    QList<QBluetoothDeviceInfo>  devices;
};