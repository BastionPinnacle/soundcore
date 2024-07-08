#include <soundcore/DeviceScanner.hpp>
#include <soundcore/DeviceList.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/range/conversion.hpp>
DeviceList::DeviceList() {
    device_scanner = std::make_unique<DeviceScanner>(*this);
}
void DeviceList::refresh()
{
    device_scanner->startScan();
}

void DeviceList::stopRefreshing() {
    device_scanner->stopScan();
}

void DeviceList::filter() {
    std::lock_guard<std::mutex> lock(mtx);
    if(device_scanner->isScanning())
    {
        qDebug() << "Cannot filter devices, scanner is running";
        return;
    }
    std::vector<Device> filtered_devices;
    for(auto& device : devices){
        if(device.name()!=""){
            filtered_devices.push_back(device);
        }
    }
    devices = std::move(filtered_devices);
}

std::vector<Device>& DeviceList::getDevices(){
    return devices;
}

void DeviceList::push(QBluetoothDeviceInfo device_info) {
    devices.push_back(Device{device_info});
}
