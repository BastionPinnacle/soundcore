#include "soundcore/connection/DeviceConnector.hpp"

DeviceConnector::State DeviceConnector::state() {
    return m_state;
}

void DeviceConnector::onInitiateConnect() {
    m_state = State::Connecting;
}

void DeviceConnector::onFinalizeConnect() {
    m_state = State::Connected;
}

void DeviceConnector::onInitiateDisconnect() {
    m_state = State::Disconnecting;
}

void DeviceConnector::onFinalizeDisconnect() {
    m_state = State::Disconnected;
}
