#pragma once

#include "soundcore/device/Device.hpp"
#include "soundcore/connection/DeviceConnector.hpp"
#include "soundcore/control/DeviceController.hpp"
#include "soundcore/discovery/DeviceDiscoverer.hpp"
#include "soundcore/list/DiscoveredDevicesInfoListModel.hpp"

class App : public QObject
{
    Q_OBJECT
public:
    App(DeviceDiscoverer&,DiscoveredDevicesInfoListModel&,DeviceController&,  QObject* parent = nullptr);
    Q_PROPERTY(DeviceConnector::State state MEMBER m_state READ state NOTIFY stateChanged)
    DeviceConnector::State state();
    signals:
    void stateChanged(DeviceConnector::State state);
public slots:
    void onStateChanged(DeviceConnector::State state);
private:
    DeviceDiscoverer& m_device_discoverer;
    DiscoveredDevicesInfoListModel& m_discovered_devices_info_list_model;
    DeviceController& m_device_controller;
    DeviceConnector m_device_connector;
    Device m_device;
    DeviceConnector::State m_state = DeviceConnector::State::Disconnected;
};