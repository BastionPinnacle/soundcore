import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import App 1.0
import DeviceConnector 1.0

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

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        color: "lightgray"
        visible: true

        Image {
            id: mainImage

            anchors.fill: parent
            source: "/images/soundcore.png"
            visible: soundcoreApp.state === DeviceConnector.Connected
        }
        Rectangle {
            anchors.centerIn: parent
            color: "#17bcef"
            height: 5 * (parent.height / 6)
            visible: true
            width: 5 * (parent.width / 6)
            Rectangle{
                anchors.fill: parent
                color: "#17bcef"
                visible: soundcoreApp.state === DeviceConnector.Disconnected
                ListView {
                    anchors.fill: parent
                    model: discoveredDevicesInfoListModel

                    delegate: Item {
                        height: 50
                        width: parent.width

                        Rectangle {
                            border.color: "black"
                            color: "lightblue"
                            height: 40
                            width: parent.width

                            Text {
                                anchors.centerIn: parent
                                font.bold: true
                                text: model.name
                            }
                        }
                    }
                }
            }

        }

    }
}

