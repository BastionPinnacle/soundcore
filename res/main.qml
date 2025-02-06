import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import App 1.0
import DeviceConnector 1.0
import DiscoveredDevicesInfoListModel 1.0

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
        visible: true

        Image {
            id: mainImage

            anchors.fill: parent
            source: "/images/soundcore.png"
            visible: soundcoreApp.state === DeviceConnector.Connected
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
                    spacing: 15  // Space between buttons

                    Button {
                        height: 40
                        text: "START"
                        width: 80

                        onClicked: {
                            console.log("START button clicked");
                            deviceDiscoverer.start();
                        }
                    }
                    Button {
                        height: 40
                        text: "STOP"
                        width: 80

                        onClicked: {
                            console.log("STOP button clicked");
                            deviceDiscoverer.stop();
                        }
                    }
                }
            }
            ListView {
                id: listView

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: discovererRect.bottom
                model: discoveredDevicesInfoListModel

                delegate: Rectangle {
                    property color clickColor: "lightblue"
                    property color hoverColor: "lightgray"

                    color: listView.isCurrentItem ? clickColor : (mouseArea.containsMouse ? hoverColor : "white")
                    height: 50
                    width: parent.width

                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 5

                        Text {
                            text: model.name
                        }
                        Button {
                            text: "CONNECT"
                            visible: discoveredDevicesInfoListModel.can_connect

                            onClicked: {
                                console.log(index);
                                discoveredDevicesInfoListModel.connectDeviceOnCurrentIndex(index);
                            }
                        }
                    }
                    /*
                    MouseArea {
                        id: mouseArea

                        anchors.fill: parent

                        onClicked: {
                            listView.currentIndex = index;
                        }
                        onReleased: {
                            parent.color = listView.isCurrentItem ? clickColor : (mouseArea.containsMouse ? hoverColor : "white");
                        }
                    }
                     */
                }
            }
        }
    }
}
