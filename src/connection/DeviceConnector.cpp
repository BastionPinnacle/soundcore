#include "soundcore/connection/DeviceConnector.hpp"

DeviceConnector::State DeviceConnector::state() {
    return m_state;
}

void DeviceConnector::onInitiateConnect() {
    m_state = State::Connecting;
    emit stateChanged(m_state);
}

void DeviceConnector::onFinalizeConnect() {
    m_state = State::Connected;
    emit stateChanged(m_state);
}

void DeviceConnector::onInitiateDisconnect() {
    m_state = State::Disconnecting;
    emit stateChanged(m_state);
}

void DeviceConnector::onFinalizeDisconnect() {
    m_state = State::Disconnected;
    emit stateChanged(m_state);
}
