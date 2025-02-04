#pragma once

#include <QObject>

#include "soundcore/Device.hpp"
#include "soundcore/DeviceInfoList.hpp"

class App : QObject
{
public:
    App(QObject* parent = nullptr);
    Q_PROPERTY(DeviceInfoList device_list READ deviceList NOTIFY deviceListChanged)
    Q_PROPERTY(Device* device READ device NOTIFY deviceChanged)
    DeviceInfoList& deviceList();
    Device* device();
    void selectDevice(std::size_t index);
private:
    DeviceInfoList m_device_list;
    Device* m_device;
};