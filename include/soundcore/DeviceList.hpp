#pragma once
#include <QObject>
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothAddress>
#include <iostream>
#include <mutex>

class DeviceList : public QAbstractListModel {
    Q_OBJECT
public:
    enum DeviceRoles {
        NameRole = Qt::UserRole + 1,
        AddressRole
    };
    DeviceList(QObject* parent=nullptr);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void stopRefreshing();
    enum State{
        Initialized,
        Refreshing,
        Refreshed
    };
    Q_ENUM(State)
    Q_INVOKABLE State getState();
    Q_INVOKABLE std::size_t numberOfDevices();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = DeviceRoles::NameRole) const override;
protected:
    QHash<int, QByteArray> roleNames() const override;
private slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device);
    //void onDeviceDiscoveryFinished();
    //void onDeviceDiscoveryStarted();
private:
    QList<QBluetoothDeviceInfo>  devices;
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    State state = State::Initialized;
};