#pragma once
#include <QObject>
#include <QBluetoothDeviceInfo>
#include "Device.hpp"
#include "DeviceScanner.hpp"
#include <iostream>

class DeviceList : public QObject {
    Q_OBJECT
public:
    void refresh();
    void filter();
public slots:

    void getNumberOfDevices(){
        std::cout<<devices.size()<<std::endl;
    }

    void onDeviceDiscovered(QBluetoothDeviceInfo device_info){
        auto device_already_exists =  checkIfAlreadyExists(device_info);
       if(!device_already_exists)
       {
           addDeviceWithInfo(device_info);
       }
    }
private:
    std::vector<Device> devices;
    bool checkIfAlreadyExists(QBluetoothDeviceInfo device_info){
        for(auto& device : devices)
        {
            auto current_device_info = device.getDeviceInfo();
            if(current_device_info.deviceUuid() == device_info.deviceUuid())
            {
                return true;
            }
        }
        return false;
    }
    void  addDeviceWithInfo(QBluetoothDeviceInfo device_info){
        Device device{device_info};
        devices.push_back(device);
    }
};