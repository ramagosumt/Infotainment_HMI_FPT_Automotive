import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true

    color: "#00ffffff"

    WeatherView {
        id: weatherViewWindow
        objectName: "weatherViewWindow"
    }
}

/*  ColumnLayout {
        id: state2

        visible: currentStateIndex === 2

        anchors.fill: parent

        z: 4

        spacing: 1

        Rectangle {
            id: rec5

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity2

                text: weatherViewModel ? weatherViewModel.currentProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec6

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                spacing: 1

                TextInput {
                    id: curTemp2

                    text: qsTr("68")
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    width: 80

                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                TextInput {
                    id: curTempMode2

                    text: qsTr("°F")
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }

    ColumnLayout {
        id: state3

        visible: currentStateIndex === 3

        anchors.fill: parent

        z: 3

        spacing: 1

        Rectangle {
            id: rec7

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity3

                text: weatherViewModel ? weatherViewModel.currentProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec8

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            TextInput {
                id: curWeather3

                text: weatherViewModel ? weatherViewModel.currentCondition : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
            }
        }
    }

    ColumnLayout {
        id: state4

        visible: currentStateIndex === 4

        anchors.fill: parent

        z: 2

        spacing: 1

        Rectangle {
            id: rec9

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity4

                text: weatherViewModel ? weatherViewModel.currentProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec10

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                spacing: 1

                TextInput {
                    id: curWind4

                    text: weatherViewModel ? weatherViewModel.currentWindSpeed : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    width: 80

                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                TextInput {
                    id: curWindMode4

                    text: weatherViewModel ? weatherViewModel.currentWindSpeedUnit : ""
                    font.pixelSize: 18
                    font.family: encodeSansThin.name

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }

    ColumnLayout {
        id: state5

        visible: currentStateIndex === 5

        anchors.fill: parent

        z: 1

        spacing: 1

        Rectangle {
            id: rec11

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity5

                text: weatherViewModel ? weatherViewModel.currentProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec12

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                spacing: 1

                TextInput {
                    id: curWind5

                    text: weatherViewModel ? weatherViewModel.destinationWindSpeed : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    width: 80

                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                TextInput {
                    id: curWindMode5

                    text: weatherViewModel ? weatherViewModel.currentWindSpeedUnit : ""
                    font.pixelSize: 18
                    font.family: encodeSansThin.name

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }
*/
/*  ColumnLayout {
        id: state7

        visible: currentStateIndex === 7

        anchors.fill: parent

        z: -2

        spacing: 1

        Rectangle {
            id: rec17

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity7

                text: weatherViewModel ? weatherViewModel.destinationProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec18

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                spacing: 1

                TextInput {
                    id: curTemp7

                    text: qsTr("73")
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    width: 80

                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                TextInput {
                    id: curTempMode7

                    text: qsTr("°F")
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }

    ColumnLayout {
        id: state8

        visible: currentStateIndex === 8

        anchors.fill: parent

        z: -3

        spacing: 1

        Rectangle {
            id: rec19

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity8

                text: weatherViewModel ? weatherViewModel.destinationProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec20

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            TextInput {
                id: curWeather8

                text: weatherViewModel ? weatherViewModel.destinationCondition : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
            }
        }
    }

    ColumnLayout {
        id: state9

        visible: currentStateIndex === 9

        anchors.fill: parent

        z: -4

        spacing: 1

        Rectangle {
            id: rec21

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity9

                text: weatherViewModel ? weatherViewModel.destinationProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec22

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                spacing: 1

                TextInput {
                    id: curWind9

                    text: weatherViewModel ? weatherViewModel.destinationWindSpeed : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    width: 80

                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                TextInput {
                    id: curWindMode9

                    text: weatherViewModel ? weatherViewModel.destinationWindSpeedUnit : ""
                    font.pixelSize: 18
                    font.family: encodeSansThin.name

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }

    ColumnLayout {
        id: state10

        visible: currentStateIndex === 10

        anchors.fill: parent

        z: -5

        spacing: 1

        Rectangle {
            id: rec23

            color: "#ffffc5"

            width: 250

            Layout.fillHeight: true

            TextInput {
                id: curCity10

                text: weatherViewModel ? weatherViewModel.destinationProvinceName : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name

                anchors.fill: parent

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignBottom
            }
        }

        Rectangle {
            id: rec24

            color: "#ffffc5"

            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                spacing: 1

                TextInput {
                    id: curWind10

                    text: qsTr("3.6")
                    font.pixelSize: 24
                    font.family: encodeSansThin.name

                    width: 80

                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                TextInput {
                    id: curWindMode10

                    text: weatherViewModel ? weatherViewModel.destinationWindSpeedUnit : ""
                    font.pixelSize: 18
                    font.family: encodeSansThin.name

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }
*/
