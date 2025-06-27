import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    title: qsTr("ARHUD WeatherApp UI")

    visible: true

    width: 756
    height: 336

    x: 25
    y: 200

    color: "#ffffc5"

    FontLoader {
        id: encodeSansThin
        source: "assets/fonts/Encode_Sans/static/EncodeSans-Thin.ttf"
    }

    ApplicationWindow {
        id: win
        title: qsTr("TreIsocraft version 0.0.0 by Tre.")

        visible: false

        width: 640
        height: 480

        x: (Screen.width - win.width) / 2
        y: (Screen.height - win.height) / 2

        color: "#ffffc5"
    }

    RowLayout {
        width: 600
        height: 50

        x: 50
        y: 250

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            MediaView {
                id: mediaViewWindow
                objectName: "mediaViewWindow"
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            WeatherView {
                id: weatherViewWindow
                objectName: "weatherViewWindow"
            }
        }
    }
}
