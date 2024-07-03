import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    id: page

    property var divisorWidth: 5

    color: "lightgray"
    height: Screen.height
    title: "Soundcore Tuner"
    visible: true
    width: Screen.width

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

                spacing: scannerRectangle.width / 50

                RoundButton {
                    id: scanButton

                    height: scannerRectangle.height / 20
                    text: "Scan"
                    width: scannerRectangle.width / 2 - parent.spacing / 2
                    radius: height / 3
                }
                RoundButton {
                    id: filterButton

                    height: scannerRectangle.height / 20
                    text: "Filter"
                    width: scannerRectangle.width / 2 - parent.spacing / 2
                    radius: height/3
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
            source: "images/soundcore.png"
        }
    }
}

