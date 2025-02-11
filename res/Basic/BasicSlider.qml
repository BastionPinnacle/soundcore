import QtQuick
import QtQuick.Controls 2.15
import Colors 1.0

Slider {
    id: singleSlider

    property int sliderWidth: 40

    from: -6
    orientation: Qt.Vertical
    stepSize: 1
    to: 6
    value: 0

    background: Rectangle {
        anchors.horizontalCenter: singleSlider.horizontalCenter
        anchors.verticalCenter: singleSlider.verticalCenter
        color: Colors.currentTheme.cardColor
        height: singleSlider.availableHeight
        implicitWidth: sliderWidth
        width: implicitWidth

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: Colors.currentTheme.caption
            height: singleSlider.availableHeight * (1 - singleSlider.visualPosition)
        }
    }
    handle: Rectangle {
        anchors.horizontalCenter: singleSlider.horizontalCenter
        color: Colors.currentTheme.borderColor
        implicitHeight: implicitWidth
        implicitWidth: sliderWidth
        y: singleSlider.topPadding + singleSlider.visualPosition * (singleSlider.availableHeight - height)
    }
}
