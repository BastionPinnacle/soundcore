#include "soundcore/connection/DeviceConnector.hpp"

DeviceConnector::State DeviceConnector::state() {
    return m_state;
}

void DeviceConnector::onInitiateConnect(QBluetoothDeviceInfo device_info) {
    qDebug() << "onInitiateConnect";
    m_state = State::Connecting;
    emit stateChanged(m_state);
    emit initiateConnect(device_info);
}

void DeviceConnector::onFinalizeConnect() {
    qDebug() << "onFinalizeConnect";
    m_state = State::Connected;
    emit stateChanged(m_state);
}

void DeviceConnector::onInitiateDisconnect() {
    qDebug() << "onInitiateDisconnect";
    m_state = State::Disconnecting;
    emit stateChanged(m_state);
    emit initiateDisconnect();
}

void DeviceConnector::onFinalizeDisconnect() {
    qDebug() << "onFinalizeDisconnect";
    m_state = State::Disconnected;
    emit stateChanged(m_state);
}
