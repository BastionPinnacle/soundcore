import QtQuick 2.0

Window {
    id: page

    property var divisorWidth: 10

    color: "lightgray"
    height: 480
    visible: true
    width: 320

        Rectangle {
            id: scannerRectangle

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.top: parent.top
            color: "lightgray"
            visible: true
            width: parent.width / 4 - parent.divisorWidth / 2

            Component.onCompleted: {
                console.log(scannerRectangle.height);
            }
        }
        Rectangle {
            id: deviceRectangle

            anchors.bottom: parent.bottom
            anchors.left: scannerRectangle.right
            anchors.right: parent.right
            anchors.top: parent.top
            color: "black"
            visible: true

        Component.onCompleted: {
            console.log(deviceRectangle.height);
        }
    }
}