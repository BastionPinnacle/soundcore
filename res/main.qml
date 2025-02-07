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

    property var divisorWidth: 5

    color: "lightgray"
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
            color: "#17bcef"
            height: 5 * (parent.height / 6)
            visible: soundcoreApp.state === DeviceConnector.Disconnected
            width: 5 * (parent.width / 6)

            Rectangle {
                id: discovererRect

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: parent.height / 4

                Row {
                    anchors.centerIn: parent
                    spacing: 20  // Increased spacing for better button alignment

                    BasicButton {
                        buttonText: deviceDiscoverer.state === DeviceDiscoverer.Idle ? "START" : "STOP"

                        onClicked: {
                            if (deviceDiscoverer.state === DeviceDiscoverer.Idle) {
                                deviceDiscoverer.start();
                            } else {
                                deviceDiscoverer.stop();
                            }
                        }
                    }
                }
            }

            // ListView for discovered devices
            ListView {
                id: listView

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: discovererRect.bottom
                model: discoveredDevicesInfoListModel

                delegate: Rectangle {
                    id: delegateRectangle

                    property color clickColor: "#A9DFBF"
                    property color hoverColor: "#F4F6F6"

                    height: parent.height / 6
                    width: parent.width

                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 15

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 18
                            text: model.name
                        }
                        BasicButton {
                            buttonText: "CONNECT"


                            onClicked: {
                                console.log(index);
                                discoveredDevicesInfoListModel.connectDeviceOnCurrentIndex(index);
                            }
                        }
                    }
                }
            }
        }

        // Connected state
        Rectangle {
            id: connectedRectangle

            anchors.centerIn: parent
            color: Colors.currentTheme.background
            height: 5 * (parent.height / 6)
            visible: soundcoreApp.state === DeviceConnector.Connected
            width: 5 * (parent.width / 6)

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
                        backgroundColor: Colors.currentTheme.background
                        anchors.centerIn: parent
                        buttonText: modelData
                        height: parent.height
                        width: parent.width

                        onClicked: {
                            console.log("Clicked:", buttonText);
                            deviceController.chooseProfile(buttonText);
                        }
                    }
                }

                Component.onCompleted: console.log(deviceController.profile_keys.length)
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
                        buttonText: modelData
                        backgroundColor: Colors.currentTheme.background
                        height: modeColumn.height / 5
                        width: modeColumn.width

                        onClicked: {
                            console.log("Clicked:", buttonText);
                            deviceController.chooseMode(buttonText);
                        }
                    }
                }
            }
            BasicButton {
                buttonText: "DISCONNECT"
                backgroundColor: Colors.currentTheme.background
                anchors.left: modeColumn.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                onClicked: {
                    deviceController.disconnectDevice();
                }
            }

        }
    }
}
