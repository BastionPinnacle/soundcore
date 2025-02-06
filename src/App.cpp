#include "soundcore/App.hpp"

App::App(DeviceDiscoverer &new_device_discoverer,
         DiscoveredDevicesInfoListModel &new_discovered_devices_info_list_model,
         DeviceController &new_device_controller, QObject *parent)
        : QObject{parent}, m_device_discoverer{new_device_discoverer},
          m_discovered_devices_info_list_model{new_discovered_devices_info_list_model},
          m_device_controller{new_device_controller} {
    // connection between DeviceDiscoverer and DiscoveredDevicesInfoListModel
    connect(&m_device_discoverer, &DeviceDiscoverer::deviceDiscovered, &m_discovered_devices_info_list_model,
            &DiscoveredDevicesInfoListModel::onDeviceDiscovered);
    connect(&m_device_discoverer, &DeviceDiscoverer::resetDiscoveredDevices, &m_discovered_devices_info_list_model,
            &DiscoveredDevicesInfoListModel::onResetDiscoveredDevices);
    connect(&m_device_discoverer, &DeviceDiscoverer::stateChanged, &m_discovered_devices_info_list_model,
            &DiscoveredDevicesInfoListModel::onStateChanged);
    // connection between DiscoveredDevicesInfoListModel and DeviceConnector
    connect(&m_discovered_devices_info_list_model, &DiscoveredDevicesInfoListModel::connectDevice, &m_device_connector,
            &DeviceConnector::onInitiateConnect);
    // connection between DeviceConnector and Device
    connect(&m_device_connector, &DeviceConnector::initiateConnect, &m_device, &Device::onInitiateConnect);
    connect(&m_device_connector, &DeviceConnector::initiateDisconnect, &m_device, &Device::onInitiateDisconnect);
    // connection between Device and DeviceConnector
    connect(&m_device, &Device::finalizeConnect, &m_device_connector, &DeviceConnector::onFinalizeConnect);
    connect(&m_device, &Device::finalizeDisconnect, &m_device_connector, &DeviceConnector::onFinalizeDisconnect);
    // connection between Device and DeviceController
    connect(&m_device, &Device::finalizeConnect, &m_device_controller, &DeviceController::onFinalizeConnect);
    connect(&m_device, &Device::finalizeDisconnect, &m_device_controller, &DeviceController::onFinalizeDisconnect);
    // connection between DeviceController and Device
    connect(&m_device_controller, &DeviceController::sendMessage, &m_device, &Device::onSendMessage);
    // connection between DeviceController and DeviceConnector
    connect(&m_device_controller, &DeviceController::initiateDisconnect, &m_device_connector,
            &DeviceConnector::onInitiateDisconnect);
    // connection between DeviceConnector and App
    connect(&m_device_connector, &DeviceConnector::stateChanged, this, &App::onStateChanged);
}

DeviceConnector::State App::state() {
    return m_state;
}


void App::onStateChanged(DeviceConnector::State state) {
    m_state = state;
    emit stateChanged(m_state);
}