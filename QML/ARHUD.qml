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
        source: "qrc:/WeatherApp_MVVM/assets/fonts/Encode_Sans/static/EncodeSans-Thin.ttf"
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

    Item {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: parent.width
        height: 150

        Item {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            width: parent.width
            height: 150

            Rectangle {
                width: 150
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                y: parent.height - 50
                color: "transparent"

                WeatherView {
                    anchors.fill: parent
                    objectName: "weatherViewWindow"
                }
            }

            Rectangle {
                width: 240
                height: 135
                x: parent.width / 2 - 150 / 2 - 60 - width
                y: parent.height - 122
                color: "transparent"

                StreamingView {
                    anchors.fill: parent
                    objectName: "streamingViewWindow"
                }
            }

            Rectangle {
                width: 150
                height: 50
                x: parent.width / 2 + 150 / 2 + 60
                y: parent.height - 50
                color: "transparent"

                MediaView {
                    anchors.fill: parent
                    objectName: "mediaViewWindow"
                }
            }
        }
    }
}
