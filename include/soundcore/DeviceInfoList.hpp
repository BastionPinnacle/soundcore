#pragma once
#include <QObject>
#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothAddress>
#include <iostream>
#include <mutex>

class DeviceInfoList : public QAbstractListModel {
    Q_OBJECT
public:
    DeviceInfoList(QObject* parent=nullptr);
    enum State{
        Initialized,
        Refreshing,
        Refreshed
    };
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void stopRefreshing();
    Q_INVOKABLE std::size_t numberOfDevices();
    Q_INVOKABLE QBluetoothDeviceInfo getDeviceInfoAt(int index) const;
    Q_ENUM(State)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    State state() const;

    enum DeviceRoles{
        NameRole = Qt::UserRole + 1,
        AddressRole
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = DeviceRoles::NameRole) const override;
protected:
    QHash<int, QByteArray> roleNames() const override;
private slots:
    void onDeviceDiscovered(QBluetoothDeviceInfo device);
    signals:
    void stateChanged(State);
private:
    void resetDevices();
    QList<QBluetoothDeviceInfo>  devices;
    QBluetoothDeviceDiscoveryAgent device_discovery_agent;
    State m_state = State::Initialized;
};