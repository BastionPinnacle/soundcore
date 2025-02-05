#pragma once

#include <QObject>
#include <QBluetoothDeviceInfo>
class DeviceConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state MEMBER m_state READ state NOTIFY stateChanged)
public:
    enum State {
        Disconnected,
        Connecting,
        Connected,
        Disconnecting
    };
    Q_ENUM(State);
    State state();
    signals:
    void stateChanged(State state);
    void initiateConnect(QBluetoothDeviceInfo device_info);
    void initiateDisconnect();
public slots:
    void onInitiateConnect();
    void onFinalizeConnect();
    void onInitiateDisconnect();
    void onFinalizeDisconnect();
private:
    State m_state;
};