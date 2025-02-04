#include "soundcore/App.hpp"

App::App(QObject* parent): QObject(parent), m_device_list(this), m_device(nullptr) {}

void App::selectDevice(std::size_t index) {
    auto device_info = m_device_list.getDeviceInfoAt(index);
    if(m_device !=nullptr)
    {
        m_device->tryToDisconnect();
        delete m_device;
    }
    m_device = new Device(device_info);
}

Device* App::device() {
    return m_device;
}

DeviceInfoList& App::deviceList(){
    return m_device_list;
}