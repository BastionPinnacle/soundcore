import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import App 1.0
import DeviceConnector 1.0
import DiscoveredDevicesInfoListModel 1.0
import DeviceDiscoverer 1.0
import Basic 1.0
import Colors 1.0

ApplicationWindow {
    id: page

    height: Screen.height
    title: "Soundcore Tuner"
    visible: true
    width: Screen.width

    Rectangle {
        id: deviceRectangle

        anchors.fill: parent
        color: Colors.currentTheme.background

        Image {
            id: mainImage

            anchors.fill: parent
            source: "/images/soundcore.png"
            visible: soundcoreApp.state === DeviceConnector.Connecting || soundcoreApp.state === DeviceConnector.Disconnecting
        }
        Rectangle {
            id: disconnectedRectangle

            anchors.centerIn: parent
            color: Colors.currentTheme.background
            height: 5 * (parent.height / 6)
            visible: soundcoreApp.state === DeviceConnector.Disconnected
            width: 5 * (parent.width / 6)

            Rectangle {
                id: discovererRect

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: parent.height / 4

                BasicButton {
                    anchors.fill: parent
                    buttonText: deviceDiscoverer.state === DeviceDiscoverer.Idle ? "START SCANNING FOR DEVICES" : "STOP SCANNING FOR DEVICES"

                    onClicked: {
                        if (deviceDiscoverer.state === DeviceDiscoverer.Idle) {
                            deviceDiscoverer.start();
                        } else {
                            deviceDiscoverer.stop();
                        }
                    }
                }
            }

            GridView {
                id: devicesGridView

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter
                anchors.top: discovererRect.bottom
                cellHeight: height / 3
                cellWidth: width / 5
                model: discoveredDevicesInfoListModel

                delegate: Rectangle {
                    id: delegateRectangle

                    color: Colors.currentTheme.cardColor
                    height: devicesGridView.cellHeight
                    width: devicesGridView.cellWidth

                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 15

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: Colors.currentTheme.textColor
                            font.pixelSize: 18
                            text: model.name
                        }
                        BasicButton {
                            anchors.horizontalCenter: parent.horizontalCenter
                            buttonText: "CONNECT"

                            onClicked: {
                                discoveredDevicesInfoListModel.connectDeviceOnCurrentIndex(index);
                            }
                        }
                    }
                }
            }
        }
        Rectangle {
            id: connectedRectangle

            property bool useCustomEqualizer: false

            anchors.centerIn: parent
            color: Colors.currentTheme.background
            height: 5 * (parent.height / 6)
            visible: soundcoreApp.state === DeviceConnector.Connected
            width: 5 * (parent.width / 6)

            Rectangle {
                anchors.fill: parent
                color: Colors.currentTheme.background
                visible: !parent.useCustomEqualizer

                GridView {
                    id: gridView

                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.horizontalCenter
                    anchors.top: parent.top
                    cellHeight: height / 11
                    cellWidth: width / 2
                    model: deviceController.profile_keys

                    delegate: Item {
                        height: gridView.cellHeight
                        width: gridView.cellWidth

                        BasicButton {
                            id: btn

                            anchors.centerIn: parent
                            backgroundColor: Colors.currentTheme.background
                            buttonText: modelData
                            height: parent.height
                            width: parent.width

                            onClicked: {
                                deviceController.chooseProfile(buttonText);
                            }
                        }
                    }
                }
                Column {
                    id: modeColumn

                    anchors.bottom: parent.bottom
                    anchors.left: gridView.right
                    anchors.top: parent.top
                    width: parent.width / 4

                    Repeater {
                        anchors.centerIn: parent
                        model: deviceController.mode_keys

                        BasicButton {
                            backgroundColor: Colors.currentTheme.background
                            buttonText: modelData
                            height: modeColumn.height / 5
                            width: modeColumn.width

                            onClicked: {
                                deviceController.chooseMode(buttonText);
                            }
                        }
                    }
                }
                BasicButton {
                    id: customEqualizerButton

                    anchors.left: modeColumn.right
                    anchors.right: parent.right
                    anchors.top: parent.top
                    backgroundColor: Colors.currentTheme.background
                    buttonText: "CUSTOM EQUALIZER"
                    height: parent.height / 2

                    onClicked: {
                        connectedRectangle.useCustomEqualizer = true;
                    }
                }
                BasicButton {
                    id: disconnectButton

                    anchors.bottom: parent.bottom
                    anchors.left: modeColumn.right
                    anchors.right: parent.right
                    anchors.top: customEqualizerButton.bottom
                    backgroundColor: Colors.currentTheme.background
                    buttonText: "DISCONNECT"

                    onClicked: {
                        deviceController.disconnectDevice();
                    }
                }
            }
            Rectangle {
                anchors.fill: parent
                color: Colors.currentTheme.background
                visible: parent.useCustomEqualizer

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.fill: parent
                    spacing: 10



                    Repeater {
                        id: kHzRepeater
                        model: deviceController.kHz
                        property var kHzList: ["100kHz", "200kHz", "400kHz", "800kHz", "1600kHz", "3200kHz", "6400kHz", "12800kHz"]

                        ColumnLayout {
                            spacing: 10

                            BasicSlider {
                                id: singleSlider

                                Layout.alignment: Qt.AlignHCenter
                                Layout.fillHeight: true
                                sliderWidth: 40
                                value: modelData

                                onPressedChanged: {
                                    if (!pressed) {
                                        deviceController.updateValue(index, value);
                                    }
                                }
                            }
                            Label {
                                Layout.alignment: Qt.AlignHCenter
                                color: "white"
                                font.bold: true
                                horizontalAlignment: Qt.AlignHCenter
                                text: kHzRepeater.kHzList[index]
                            }
                        }
                    }
                }
            }
        }
    }
}
