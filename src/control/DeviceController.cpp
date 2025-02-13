#include <QMap>
#include "soundcore/control/DeviceController.hpp"
#include <QQmlEngine>


DeviceController::DeviceController(QObject *parent) : QObject(parent) {
    connect(this, &DeviceController::kHzChanged, this, &DeviceController::onKHzChanged);
}

QStringList DeviceController::profileKeys() const {
    return m_equalizer_profiles.keys();
}

QStringList DeviceController::modeKeys() const {
    return m_modes.keys();
}

void DeviceController::onFinalizeDisconnect() {
    m_control_available = false;
}

void DeviceController::onFinalizeConnect() {
    m_control_available = true;
}

bool DeviceController::controlAvailable() const {
    return m_control_available;
}

void DeviceController::disconnectDevice() {
    emit initiateDisconnect();
}

const QMap<QString, QString> DeviceController::m_equalizer_profiles = {
        {"SoundCore Signature", "08ee00000002811400000078787878787878784d"},
        {"Acoustic",            "08ee000000028114000100a0828c8ca0a0a08c34"},
        {"Bass Booster",        "08ee000000028114000200a0968278787878789f"},
        {"Bass Reducer",        "08ee000000028114000300505a6e787878787800"},
        {"Classical",           "08ee00000002811400040096966464788c96a0bf"},
        {"Podcast",             "08ee0000000281140005005a8ca0a0968c7864b6"},
        {"Dance",               "08ee0000000281140006008c5a6e828c8c825a5d"},
        {"Deep",                "08ee0000000281140007008c8296968c64504654"},
        {"Electronic",          "08ee000000028114000800968c648c828c9696e1"},
        {"Flat",                "08ee00000002811400090064646e7878786464fc"},
        {"Hip-Hop",             "08ee000000028114000a008c966e6e8c6e8c96b1"},
        {"Jazz",                "08ee000000028114000b008c8c6464788c96a0b2"},
        {"Latin",               "08ee000000028114000c0078786464647896aa6d"},
        {"Lounge",              "08ee000000028114000d006e8ca09678648c82b4"},
        {"Piano",               "08ee000000028114000e007896968ca0aa96a04b"},
        {"Pop",                 "08ee000000028114000f006e829696826e645a66"},
        {"R&B",                 "08ee000000028114001000b48c64648c9696a0fd"},
        {"Rock",                "08ee000000028114001100968c6e6e82969696e0"},
        {"Small Speaker(s)",    "08ee000000028114001200a0968278645a50502d"},
        {"Spoken Word",         "08ee0000000281140013005a64828c8c82785a4c"},
        {"Treble Booster",      "08ee0000000281140014006464646e828c8ca075"},
        {"Treble Reducer",      "08ee000000028114001500787878645a50503ca4"}};

const QMap<QString, QString> DeviceController::m_modes = {
        {"Transparency",  "08ee00000006810e00010101008e"},
        {"Normal",        "08ee00000006810e00020101008f"},
        {"ANC Indoor",    "08ee00000006810e00000201008e"},
        {"ANC Outdoor",   "08ee00000006810e00000101008d"},
        {"ANC Transport", "08ee00000006810e00000001008c"}
};

const QByteArray DeviceController::m_ack_message = QByteArray::fromHex("09ff00000102810a0096");

void DeviceController::chooseProfile(QString profile) {
    if (m_equalizer_profiles.contains(profile)) {
        QByteArray message = m_equalizer_profiles[profile].toStdString().c_str();
        auto hex_message = QByteArray::fromHex(message);
        emit sendMessage(hex_message);
    }
}

void DeviceController::chooseMode(QString mode) {
    if (m_modes.contains(mode)) {
        QByteArray message = m_modes[mode].toStdString().c_str();
        auto hex_message = QByteArray::fromHex(message);
        emit sendMessage(hex_message);
    }

}

QList<int> DeviceController::kHz(){
    return m_kHz;
}

void DeviceController::onKHzChanged() {
    auto message = QByteArray::fromHex("08ee00000002811400fefe");
    foreach(auto value, m_kHz){
            value = value & 0xFF;
            qDebug() << value;
            auto hex_string_value = QString::number(value, 16);
            auto hex_value = QByteArray::fromHex(hex_string_value.toStdString().c_str());
            message.append(hex_value);
        };
    int crc = 0;
    foreach(auto byte, message){
        crc+=byte;
    };
    crc &= 0xFF;
    auto hex_string_crc = QString::number(crc,16);
    auto hex_crc = QByteArray::fromHex(hex_string_crc.toStdString().c_str());
    message.append(hex_crc);
    sendMessage(message);
}

void DeviceController::updateValue(int index, int value) {
    if (index >= 0 && index < m_kHz.size()) {
        m_kHz[index] = value;
        emit kHzChanged();
    }
}

void DeviceController::onReceivedMessage(QByteArray message) {
    int index = message.indexOf(m_ack_message);
    while (index != -1) {
        message.remove(index, m_ack_message.length());
        index = message.indexOf(m_ack_message);
    }
    qDebug() << message.toHex();
    message = message.right(70);
    if(message.size() >= 70)
    {
        bool changed = false;
        for(int i = 0 ; i < 8; i++)
        {
            auto byte_value = message.mid(13+i,1).toHex();
            auto int_value = byte_value.toInt(nullptr,16);
            if(m_kHz[i]!=int_value)
            {
                m_kHz[i] = int_value;
                changed = true;
            }
        }
        if(changed){
            emit kHzChanged();
        }
    }
}