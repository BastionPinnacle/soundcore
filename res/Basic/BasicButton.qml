// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtQuick
import QtQuick.Controls.Basic
import Colors

Button {
    // Height, width and any other size related properties containing odd looking float or other dividers
    // that do not seem to have any logical origin are just arbitrary and based on original design
    // and/or personal preference on what looks nice.
    id: button

    property string buttonColor: "grey"
    property string buttonText: ""
    property alias rectangle: rectangle
    property bool showIcon: true

    contentItem: Rectangle {
        id: rectangle

        anchors.fill: parent
        border.color: Colors.border
        border.width: 1
        radius: 10

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Text {
                color: (buttonColor == "green") ? Colors.dark.textColor : Colors.currentTheme.textColor
                font.pixelSize: 18
                font.weight: 700
                rightPadding: 8
                text: buttonText
            }
            Image {
                id: icon

                source: (Colors.currentTheme == Colors.dark) ? "./images/icons/keyboard_backspace_white_right.svg" : "./images/icons/keyboard_backspace_black_right.svg"
                visible: showIcon
            }
        }
    }
    states: State {
        name: "pressed"
        when: button.pressed

        PropertyChanges {
            scale: 0.9
            target: rectangle
        }
    }
    transitions: Transition {
        NumberAnimation {
            duration: 10
            easing.type: Easing.InOutQuad
            properties: "scale"
        }
    }

    rectangle.gradient: if (buttonColor == "grey"
                                && Colors.currentTheme == Colors.dark) {
                            Colors.darkButtonGradient
                        } else if (buttonColor == "grey"
                                   && Colors.currentTheme == Colors.light) {
                            Colors.lightButtonGradient
                        } else {
                            Colors.greenButtonGradient
                        }
}