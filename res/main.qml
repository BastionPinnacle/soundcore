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

            Rectangle {
                anchors.fill: parent
                color: "#17bcef"
                visible: soundcoreApp.state === DeviceConnector.Disconnected

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
                ListModel {
                    id: contactsModel
                    ListElement {
                        name: "Bill Smith"
                        position: "Engineer"
                    }
                    ListElement {
                        name: "John Brown"
                        position: "Engineer"
                    }
                    ListElement {
                        name: "Sam Wise"
                        position: "Manager"
                    }
                }
                ListView {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: discovererRect.bottom
                    model: contactsModel
                    delegate: Text{
                        text: model.name
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        console.log("Model type:", typeof discoveredDevicesInfoListModel);
        if (typeof discoveredDevicesInfoListModel === "undefined") {
            console.warn("discoveredDevicesInfoListModel is not defined!");
        } else {
            console.log("discoveredDevicesInfoListModel is available.");
        }
    }
}

