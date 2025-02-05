#include "soundcore/control/DeviceController.hpp"

QStringList DeviceController::profileKeys() const {
    return equalizer_profiles.keys();
}
QStringList DeviceController::modeKeys() const {
    return modes.keys();
}

void DeviceController::onModeKeyChosen(QString mode) {
    if(modes.contains(mode))
    {
        auto message = modes[mode];
        auto hexMessage = message.toUtf8();
        emit sendMessage(hexMessage);
    }
}

void DeviceController::onProfileKeyChosen(QString profile) {
    if(equalizer_profiles.contains(profile))
    {
        auto message = equalizer_profiles[profile];
        auto hexMessage = message.toUtf8();
        emit sendMessage(hexMessage);
    }
}

    const QHash<QString, QString> DeviceController::equalizer_profiles = {
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

const QHash<QString, QString> DeviceController::modes = {
        {"Transparency",  "08ee00000006810e00010101008e"},
        {"Normal",        "08ee00000006810e00020101008f"},
        {"ANC Indoor",    "08ee00000006810e00000201008e"},
        {"ANC Outdoor",   "08ee00000006810e00000101008d"},
        {"ANC Transport", "08ee00000006810e00000001008c"}
};