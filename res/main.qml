import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import soundcore 1.0


ApplicationWindow {
    id: page

    property var divisorWidth: 5

    color: "lightgray"
    height: Screen.height
    title: "Soundcore Tuner"
    visible: true
    width: Screen.width

    DeviceList{
        id: deviceList
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
                    }
                }
                RoundButton {
                    id: filterButton

                    height: parent.height
                    radius: height / 3
                    text: "Filter for Soundcore"
                    width: parent.width / 2 - parent.spacing / 2

                    onClicked: {
                        console.log("Filter for soundcore clicked");
                    }
                }
            }
            ListView {
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
                height: (parent.height * 19) / 20
                orientation: ListView.Vertical
                width: parent.width
                clip: true

                delegate: Rectangle {
                    color: bgcolor
                    height: 100
                    width: parent.width
                }
                model: ListModel {
                    ListElement {
                        bgcolor: 'red'
                    }
                    ListElement {
                        bgcolor: 'yellow'
                    }
                    ListElement {
                        bgcolor: 'white'
                    }
                    ListElement {
                        bgcolor: 'blue'
                    }
                    ListElement {
                        bgcolor: 'green'
                    }
                    ListElement {
                        bgcolor: 'orange'
                    }
                    ListElement {
                        bgcolor: 'black'
                    }
                    ListElement {
                        bgcolor: 'gray'
                    }
                    ListElement {
                        bgcolor: 'red'
                    }
                    ListElement {
                        bgcolor: 'yellow'
                    }
                    ListElement {
                        bgcolor: 'white'
                    }
                    ListElement {
                        bgcolor: 'blue'
                    }
                    ListElement {
                        bgcolor: 'green'
                    }
                    ListElement {
                        bgcolor: 'orange'
                    }
                    ListElement {
                        bgcolor: 'black'
                    }
                    ListElement {
                        bgcolor: 'gray'
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

