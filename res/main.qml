import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts
import DeviceList 1.0

ApplicationWindow {
    id: page

    property var divisorWidth: 5

    color: "lightgray"
    height: Screen.height
    title: "Soundcore Tuner"
    visible: true
    width: Screen.width

    DeviceList {
        id: device_list
    }
    Rectangle {
        id: scannerRectangle

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        color: "#17bcef"
        visible: true
        width: page.width / 4 - divisorWidth / 2

        Column {
            id: scanColumn

            anchors.fill: parent

            Row {
                id: controlRow

                height: parent.height / 20
                spacing: scannerRectangle.width / 50
                width: parent.width

                RoundButton {
                    id: scanButton

                    height: parent.height
                    radius: height / 3
                    text: "Scan for Devices"
                    width: parent.width / 2 - parent.spacing / 2

                    onClicked: {
                        console.log("Scan for devices clicked");
                        device_list.refresh();
                    }
                }
                RoundButton {
                    id: filterButton

                    height: parent.height
                    radius: height / 3
                    text: "Stop scannning for Devices "
                    width: parent.width / 2 - parent.spacing / 2

                    onClicked: {
                        console.log("Stop scanning for devices clicked");
                        device_list.stopRefreshing();
                    }
                }
            }
            ListView {
                id: listView

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: controlRow.bottom
                model: devie_list

                delegate: RowLayout {
                    height: parent.height
                    width: parent.width

                    Text {
                        color: "white"
                        font.pixelSize: 24
                        text: name + " (" + address + ")"
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    ToolButton {
                        text: "x"

                        onClicked: {
                            console.log("X CLICKED");
                        }
                    }
                }
            }
        }
    }
    Rectangle {
        id: divisorRectangle

        anchors.bottom: parent.bottom
        anchors.left: scannerRectangle.right
        anchors.top: parent.top
        color: "white"
        visible: true
        width: divisorWidth
    }
    Rectangle {
        id: deviceRectangle

        anchors.bottom: parent.bottom
        anchors.left: divisorRectangle.right
        anchors.right: parent.right
        anchors.top: parent.top
        color: "#17bcef"
        visible: true

        Image {
            id: mainImage

            anchors.fill: parent
            source: "/images/soundcore.png"
        }
    }
}

