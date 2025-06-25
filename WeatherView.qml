import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    objectName: "weatherViewWindow"

    visible: true

    property int displayDuration: 2000
    property int scrollDuration: 1000
    property int itemHeight: 100

    property int currentIndex: 0
    property int destinationIndex: 0

    property var currentBlockModel: [
        currentTemperatureComponent,
        currentConditionComponent,
        currentWindComponent
    ]

    property var destinationBlockModel: [
        destinationTemperatureComponent,
        destinationConditionComponent,
        destinationWindComponent
    ]

    Timer {
        id: scrollTimer
        interval: displayDuration + scrollDuration
        repeat: true
        running: true

        onTriggered: {
            if (currentIndex < currentBlockModel.length - 1) {
                currentIndex += 1
                scrollAnim.to = currentIndex * itemHeight
                scrollAnim.running = true
            } else {
                Qt.callLater(() => jumpTimer.start())
                scrollTimer.stop()
            }
        }
    }

    Timer {
        id: jumpTimer
        interval: scrollDuration
        repeat: false
        onTriggered: {
            listView.contentY = 0
            currentIndex = 0
            rowWeather1.visible = false
            rowWeather2.visible = true

            scrollTimer.stop()
            destinationScrollTimer.start()
        }
    }

    Timer {
        id: destinationScrollTimer
        interval: displayDuration + scrollDuration
        repeat: true
        running: true

        onTriggered: {
            if (destinationIndex < destinationBlockModel.length - 1) {
                destinationIndex += 1
                destinationScrollAnim.to = destinationIndex * itemHeight
                destinationScrollAnim.running = true
            } else {
                Qt.callLater(() => destinationJumpTimer.start())
                destinationScrollTimer.stop()
            }
        }
    }

    Timer {
        id: destinationJumpTimer
        interval: scrollDuration
        repeat: false
        onTriggered: {
            destinationListView.contentY = 0
            destinationIndex = 0
            rowWeather1.visible = true
            rowWeather2.visible = false

            destinationScrollTimer.stop()
            scrollTimer.start()
        }
    }

    Component {
        id: currentTemperatureComponent
        Rectangle {
            width: parent.width
            height: itemHeight
            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 1

                Text {
                    text: weatherViewModel ? weatherViewModel.currentTemperature : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    width: 80
                    Layout.fillHeight: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                Text {
                    text: weatherViewModel ? weatherViewModel.currentTemperatureUnit : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }

    Component {
        id: currentConditionComponent
        Rectangle {
            width: parent.width
            height: itemHeight
            color: "transparent"

            Text {
                text: weatherViewModel ? weatherViewModel.currentCondition : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name
                font.weight: Font.Thin
                color: "#000000"
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
            }
        }
    }

    Component {
        id: currentWindComponent
        Rectangle {
            width: parent.width
            height: itemHeight
            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 1

                Text {
                    text: weatherViewModel ? weatherViewModel.currentWindSpeed : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    width: 80
                    Layout.fillHeight: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                Text {
                    text: weatherViewModel ? weatherViewModel.currentWindSpeedUnit : ""
                    font.pixelSize: 18
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }

    Component {
        id: destinationTemperatureComponent
        Rectangle {
            width: parent.width
            height: itemHeight
            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 1

                Text {
                    text: weatherViewModel ? weatherViewModel.destinationTemperature : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    width: 80
                    Layout.fillHeight: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                Text {
                    text: weatherViewModel ? weatherViewModel.destinationTemperatureUnit : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }

    Component {
        id: destinationConditionComponent
        Rectangle {
            width: parent.width
            height: itemHeight
            color: "transparent"

            Text {
                text: weatherViewModel ? weatherViewModel.destinationCondition : ""
                font.pixelSize: 24
                font.family: encodeSansThin.name
                font.weight: Font.Thin
                color: "#000000"
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
            }
        }
    }

    Component {
        id: destinationWindComponent
        Rectangle {
            width: parent.width
            height: itemHeight
            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 1

                Text {
                    text: weatherViewModel ? weatherViewModel.destinationWindSpeed : ""
                    font.pixelSize: 24
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    width: 80
                    Layout.fillHeight: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }

                Text {
                    text: weatherViewModel ? weatherViewModel.destinationWindSpeedUnit : ""
                    font.pixelSize: 18
                    font.family: encodeSansThin.name
                    font.weight: Font.Thin
                    color: "#000000"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }

    RowLayout {
        id: rowWeather1
        width: 100
        height: 75
        z: 2
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 1

        Rectangle {
            width: 50
            color: "transparent"
            Layout.fillHeight: true

            Image {
                anchors.fill: parent
                source: weatherViewModel ? weatherViewModel.currentConditionIcon : ""
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle {
            width: 75
            color: "transparent"
            Layout.fillHeight: true

            ColumnLayout {
                anchors.fill: parent
                z: 2
                spacing: 1

                Rectangle {
                    width: 250
                    Layout.fillHeight: true
                    color: "transparent"

                    Text {
                        text: weatherViewModel ? weatherViewModel.currentProvinceName : ""
                        font.pixelSize: 24
                        font.family: encodeSansThin.name
                        font.weight: Font.Thin
                        color: "#000000"
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignBottom
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    color: "transparent"

                    ListView {
                        id: listView
                        width: parent.width
                        height: parent.height
                        model: currentBlockModel
                        interactive: false
                        boundsBehavior: Flickable.StopAtBounds
                        orientation: ListView.Vertical
                        contentY: 0

                        delegate: Loader {
                            width: parent.width
                            height: itemHeight
                            sourceComponent: modelData
                        }
                    }

                    NumberAnimation {
                        id: scrollAnim
                        target: listView
                        property: "contentY"
                        duration: scrollDuration
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }

    RowLayout {
        id: rowWeather2
        width: 100
        height: 75
        visible: false
        z: 1
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 1

        Rectangle {
            width: 50
            color: "transparent"
            Layout.fillHeight: true

            Image {
                anchors.fill: parent
                source: weatherViewModel ? weatherViewModel.destinationConditionIcon : ""
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle {
            width: 75
            color: "transparent"
            Layout.fillHeight: true

            ColumnLayout {
                anchors.fill: parent
                z: 1
                spacing: 1

                Rectangle {
                    width: 250
                    Layout.fillHeight: true
                    color: "transparent"

                    Text {
                        text: weatherViewModel ? weatherViewModel.destinationProvinceName : ""
                        font.pixelSize: 24
                        font.family: encodeSansThin.name
                        font.weight: Font.Thin
                        color: "#000000"
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignBottom
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    color: "transparent"

                    ListView {
                        id: destinationListView
                        width: parent.width
                        height: parent.height
                        model: destinationBlockModel
                        interactive: false
                        boundsBehavior: Flickable.StopAtBounds
                        orientation: ListView.Vertical
                        contentY: 0

                        delegate: Loader {
                            width: parent.width
                            height: itemHeight
                            sourceComponent: modelData
                        }
                    }

                    NumberAnimation {
                        id: destinationScrollAnim
                        target: destinationListView
                        property: "contentY"
                        duration: scrollDuration
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}
