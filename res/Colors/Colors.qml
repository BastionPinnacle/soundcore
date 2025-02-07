pragma Singleton
import QtQuick

Item {
    property color border: "#898989"
    property var currentTheme: dark
    property alias dark: dark
    property alias darkButtonGradient: darkButtonGradient
    property color green: "#1FC974"
    property alias greenBorder: greenBorder
    property alias greenButtonGradient: greenButtonGradient
    property color grey: "#585858"
    property alias greyBorder: greyBorder
    property alias invertedGreenBorder: invertedGreenBorder
    property alias invertedGreyBorder: invertedGreyBorder
    property alias light: light
    property alias lightButtonGradient: lightButtonGradient
    property color shadow: "white"

    QtObject {
        id: light

        readonly property color background: "#ffffff"
        readonly property color borderColor: "#D8D8D8"
        readonly property color caption: "#898989"
        readonly property color cardColor: "#FFFFFF"
        readonly property color textColor: "#121111"
    }
    QtObject {
        id: dark

        readonly property color background: "#121212"
        readonly property color borderColor: "#3E3E3E"
        readonly property color caption: "#898989"
        readonly property color cardColor: "#212121"
        readonly property color textColor: "#FEFEFE"
    }
    Gradient {
        id: invertedGreyBorder

        GradientStop {
            color: currentTheme.cardColor
            position: 0.0
        }
        GradientStop {
            color: currentTheme.borderColor
            position: 1.0
        }
    }
    Gradient {
        id: greyBorder

        GradientStop {
            color: currentTheme.borderColor
            position: 0.0
        }
        GradientStop {
            color: currentTheme.cardColor
            position: 1.0
        }
    }
    Gradient {
        id: invertedGreenBorder

        // GradientStop positions are arbitrary
        GradientStop {
            color: "#18B969"
            position: 1.0
        }
        GradientStop {
            color: "#c718b969"
            position: 0.66
        }
        GradientStop {
            color: "#ab18b969"
            position: 0.33
        }
        GradientStop {
            color: currentTheme.cardColor
            position: 0.0
        }
    }
    Gradient {
        id: greenBorder

        GradientStop {
            color: currentTheme.cardColor
            position: 1.0
        }
        GradientStop {
            color: "#ab18b969"
            position: 0.66
        }
        GradientStop {
            color: "#c718b969"
            position: 0.33
        }
        GradientStop {
            color: "#18B969"
            position: 0.0
        }
    }
    Gradient {
        id: greenButtonGradient

        GradientStop {
            color: "#2CDE85"
            position: 0.3
        }
        GradientStop {
            color: "#24b46d"
            position: 0.5
        }
        GradientStop {
            color: "#9c219d60"
            position: 0.9
        }
    }
    Gradient {
        id: darkButtonGradient

        GradientStop {
            color: Colors.currentTheme.background
            position: 0.2
        }
        GradientStop {
            color: "#2a2a2a"
            position: 0.5
        }
        GradientStop {
            color: "#f72a2a2a"
            position: 0.9
        }
    }
    Gradient {
        id: lightButtonGradient

        GradientStop {
            color: Colors.currentTheme.background
            position: 0.2
        }
        GradientStop {
            color: "#eeeeee"
            position: 0.5
        }
        GradientStop {
            color: "#e6e6e6"
            position: 0.9
        }
    }
}