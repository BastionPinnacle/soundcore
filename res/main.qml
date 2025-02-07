import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import App 1.0
import DeviceConnector 1.0
import DiscoveredDevicesInfoListModel 1.0
import DeviceDiscoverer 1.0
import Basic 1.0

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
        color: "lightgray"

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
                        /*
                        font.pixelSize: 18
                        height: 50
                        text: deviceDiscoverer.state === DeviceDiscoverer.Idle ? "START" : "STOP"
                        width: 100

                        background: Rectangle {
                            border.color: "#2980b9"
                            border.width: 2
                            color: "#3498db"
                            radius: 25
                        }
                         */
                        text: deviceDiscoverer.state === DeviceDiscoverer.Idle ? "START" : "STOP"
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
                        Button {
                            font.pixelSize: 16
                            text: "CONNECT"
                            visible: discoveredDevicesInfoListModel.can_connect
                            width: 150

                            background: Rectangle {
                                border.color: "#2980b9"
                                border.width: 2
                                color: "#3498db"
                                radius: 25
                            }

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
            color: "#17bcef"
            height: 5 * (parent.height / 6)
            visible: soundcoreApp.state === DeviceConnector.Connected
            width: 5 * (parent.width / 6)

            Row {
                anchors.centerIn: parent
                spacing: 30  // Increase spacing for better layout

                Column {
                    spacing: 10

                    Repeater {
                        model: deviceController.profile_keys

                        Button {
                            font.pixelSize: 18
                            height: 20
                            text: modelData
                            width: 200

                            background: Rectangle {
                                border.color: "#2980b9"
                                border.width: 2
                                color: "#3498db"
                                radius: 25
                            }

                            onClicked: {
                                console.log("Clicked:", text);
                                deviceController.chooseProfile(text);
                            }
                        }
                    }
                }
                Column {
                    spacing: 20

                    Repeater {
                        model: deviceController.mode_keys

                        Button {
                            font.pixelSize: 18
                            height: 50
                            text: modelData
                            width: 200

                            background: Rectangle {
                                border.color: "#2980b9"
                                border.width: 2
                                color: "#3498db"
                                radius: 25
                            }

                            onClicked: {
                                console.log("Clicked:", text);
                                deviceController.chooseMode(text);
                            }
                        }
                    }
                }
                Button {
                    font.pixelSize: 18
                    height: 50
                    text: "Disconnect"
                    width: 200

                    background: Rectangle {
                        border.color: "#2980b9"
                        border.width: 2
                        color: "#3498db"
                        radius: 25
                    }

                    onClicked: {
                        deviceController.disconnectDevice()
                    }
                }
            }
        }
    }
}
