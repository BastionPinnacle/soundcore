import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts
import App 1.0
import DeviceConnector 1.0
import DiscoveredDevicesInfoListModel 1.0
import DeviceDiscoverer 1.0
import Basic 1.0
import Colors 1.0

ApplicationWindow {
    id: page

    height: Screen.height
    title: "Soundcore Tuner"
    visible: true
    width: Screen.width

    Rectangle {
        id: deviceRectangle

        anchors.fill: parent
        color: Colors.currentTheme.background
        visible: soundcoreApp.state === DeviceConnector.Disconnected

        Button {
            id: scanButton

            property int diameter: Math.min(parent.width, parent.height) / 3

            anchors.centerIn: parent
            height: diameter
            text: "SCAN"
            width: diameter

            background: Rectangle {
                border.color: Colors.curentTheme.borderColor
                border.width: 5
                color: Colors.currentTheme.cardColor
                radius: scanButton.diameter / 2
            }
            contentItem: Text {
                color: Colors.currentTheme.textColor
                font.pixelSize: parent.diameter / 3
                horizontalAlignment: Text.AlignHCenter
                text: parent.text
                verticalAlignment: Text.AlignVCenter
            }

            onPressed: {
                console.log("Main button pressed!");
                deviceDiscoverer.start();
                buttonScaleAnimation.start();
                buttonColorAnimation.start();
            }

            NumberAnimation {
                id: buttonScaleAnimation

                duration: 100
                easing.type: Easing.OutQuad
                from: 1.0
                property: "scale"
                target: scanButton
                to: 1.1

                onFinished: scanButton.scale = 1.0
            }
            ColorAnimation {
                id: buttonColorAnimation

                duration: 200
                easing.type: Easing.InOutQuad
                from: Colors.currentTheme.cardColor
                property: "background.color"
                target: scanButton
                to: "white"

                onFinished: scanButton.background.color = Colors.currentTheme.cardColor
            }
            Repeater {
                model: discoveredDevicesInfoListModel

                delegate: Shape {
                    id: arcShape

                    property int numberOfDevices: discoveredDevicesInfoListModel.count
                    property int numberOfHypotheticalDevices: Math.max(numberOfDevices, 20)
                    property int singleElementAngle: 360 / numberOfHypotheticalDevices

                    anchors.centerIn: scanButton
                    height: (scanButton.diameter) * 2
                    layer.enabled: true
                    layer.samples: 4
                    width: (scanButton.diameter) * 2

                    ShapePath {
                        id: shapePath

                        capStyle: ShapePath.FlatCap
                        fillColor: "transparent"
                        strokeColor: Colors.currentTheme.cardColor
                        strokeWidth: (scanButton.diameter) / 2

                        PathAngleArc {
                            id: pathAngleArc

                            centerX: arcShape.width / 2
                            centerY: arcShape.height / 2
                            radiusX: (scanButton.diameter / 2) + shapePath.strokeWidth / 2
                            radiusY: (scanButton.diameter / 2) + shapePath.strokeWidth / 2
                            startAngle: singleElementAngle * index
                            sweepAngle: singleElementAngle * (index + 1)
                        }
                    }
                    Text {
                        color: Colors.currentTheme.textColor
                        font.bold: true
                        font.pixelSize: 20
                        rotation: (pathAngleArc.startAngle + pathAngleArc.sweepAngle) / 2
                        text: model.name
                        x: pathAngleArc.centerX + Math.cos(Math.PI * ((pathAngleArc.startAngle + pathAngleArc.sweepAngle) / 2) / 180) * ((scanButton.diameter / 2) + 10)
                        y: pathAngleArc.centerY + Math.sin(Math.PI * ((pathAngleArc.startAngle + pathAngleArc.sweepAngle) / 2) / 180) * ((scanButton.diameter / 2) + 10)
                    }
                    MouseArea {
                        anchors.fill: parent
                        propagateComposedEvents: true

                        onClicked: mouse => {
                            var dx = mouse.x - arcShape.width / 2;
                            var dy = mouse.y - arcShape.height / 2;
                            var distance = Math.sqrt(dx * dx + dy * dy);
                            console.log(distance);
                            console.log(pathAngleArc.radiusX);
                            console.log(pathAngleArc.radiusX + shapePath.strokeWidth);
                            if (distance >= (scanButton.diameter / 2) && distance <= (scanButton.diameter / 2) + shapePath.strokeWidth) {
                                discoveredDevicesInfoListModel.connectDeviceOnCurrentIndex(index);
                                arcScaleAnimation.start();
                                colorChangeAnimation.start();
                            } else {
                                if (distance <= (scanButton.diameter / 2)) {
                                    scanButton.onPressed();
                                }
                            }
                        }
                    }
                    NumberAnimation {
                        id: arcScaleAnimation

                        duration: 100
                        easing.type: Easing.OutQuad
                        from: 1.0
                        property: "scale"
                        target: arcShape
                        to: 1.1

                        onFinished: arcShape.scale = 1.0
                    }
                    ColorAnimation {
                        id: colorChangeAnimation

                        duration: 200
                        easing.type: Easing.InOutQuad
                        from: Colors.currentTheme.cardColor
                        property: "strokeColor"
                        target: shapePath
                        to: "white"

                        onFinished: shapePath.strokeColor = Colors.currentTheme.cardColor
                    }
                }
            }
        }
    }
    Rectangle {
        anchors.fill: parent
        color: Colors.currentTheme.background
        visible: soundcoreApp.state === DeviceConnector.Connected

        RowLayout {
            anchors.fill: parent
            spacing: 10

            Repeater {
                id: kHzRepeater

                property var kHzList: ["100kHz", "200kHz", "400kHz", "800kHz", "1600kHz", "3200kHz", "6400kHz", "12800kHz"]

                model: deviceController.kHz

                ColumnLayout {
                    spacing: 10

                    BasicSlider {
                        id: singleSlider

                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillHeight: true
                        sliderWidth: 40
                        value: modelData

                        onPressedChanged: {
                            if (!pressed) {
                                deviceController.updateValue(index, value);
                            }
                        }
                    }
                    Label {
                        Layout.alignment: Qt.AlignHCenter
                        color: "white"
                        font.bold: true
                        text: kHzRepeater.kHzList[index]
                    }
                }
            }
            Rectangle {
                Layout.fillHeight: true
                color: Colors.currentTheme.background
                width: 200

                ListView {
                    id: profileListView

                    height: Math.min(contentHeight, parent.height - y)
                    interactive: false
                    model: deviceController.profile_keys
                    width: parent.width
                    y: parent.height / 10

                    delegate: BasicButton {
                        id: btn

                        backgroundColor: Colors.currentTheme.cardColor
                        buttonText: modelData
                        height: implicitHeight
                        implicitHeight: 40
                        width: profileListView.width

                        onClicked: {
                            deviceController.chooseProfile(buttonText);
                        }
                    }
                }
            }
            Rectangle {
                Layout.fillHeight: true
                color: Colors.currentTheme.background
                width: 200

                ListView {
                    id: modeListView

                    height: Math.min(contentHeight, parent.height - y)
                    interactive: false
                    model: deviceController.mode_keys
                    width: parent.width
                    y: parent.height / 10

                    delegate: BasicButton {
                        id: btn

                        backgroundColor: Colors.currentTheme.cardColor
                        buttonText: modelData
                        height: implicitHeight
                        implicitHeight: 40
                        implicitWidth: 200
                        width: implicitWidth

                        onClicked: {
                            deviceController.chooseMode(buttonText);
                        }
                    }
                }
                BasicButton {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height/10
                    backgroundColor: Colors.currentTheme.cardColor
                    buttonText: "DISCONNECT"
                    height: implicitHeight
                    implicitHeight: 40
                    implicitWidth: 200
                    width: implicitWidth

                    onClicked: {
                        deviceController.disconnectDevice();
                    }
                }
            }
        }
    }
}
