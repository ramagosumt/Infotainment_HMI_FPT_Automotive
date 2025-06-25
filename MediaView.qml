import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
    id: win
    objectName: "mediaViewWindow"

    visible: true

    property int horizontalScrollPeriod: 17
    property bool didFirstScroll: false
    property bool onTextChangedFromNextLoop: false

    Timer {
        id: updateTimer

        interval: 100
        repeat: true
        running: true

        onTriggered: {
            if (mediaViewModel.getCurrentDurationRaw() <= 0) return

            let newTime = Math.min(mediaViewModel.currentTimeRaw + interval,
                                   mediaViewModel.getCurrentDurationRaw())

            mediaViewModel.setCurrentTime(newTime)
        }
    }

    RowLayout {
        width: 100
        height: 75

        spacing: 1

        Rectangle {
            id: iconRect

            width: 50

            color: "transparent"

            Layout.fillHeight: true

            Image {
                anchors.fill: parent
                source: mediaViewModel ? mediaViewModel.currentSourceIcon : ""
                fillMode: Image.PreserveAspectFit
            }
        }

        ColumnLayout {
            spacing: 2

            Rectangle {
                width: 150

                color: "transparent"

                Layout.fillHeight: true

                Rectangle {
                    id: clipRect

                    width: parent.width
                    height: parent.height

                    color: "transparent"

                    clip: true

                    Text {
                        id: scrollText

                        text: getSongDisplayText()

                        function getSongDisplayText() {
                            if (mediaViewModel) {
                                let song = mediaViewModel.currentSong
                                let artist = mediaViewModel.currentArtist
                                let album = mediaViewModel.currentAlbum

                                if ((!song || song.length === 0) && (!artist || artist.length === 0)) return ""

                                return album && album.length > 0 ? `${song} – ${artist} (${album})` : `${song} – ${artist}`
                            }

                            return ""
                        }

                        font.pixelSize: 24
                        font.family: encodeSansThin.name
                        font.weight: Font.Thin

                        color: "#000000"

                        renderType: Text.NativeRendering

                        x: 0
                        y: clipRect.height - height

                        property string lastText: ""

                        SequentialAnimation on x {
                            id: firstShortAnim
                            running: false

                            NumberAnimation {
                                from: 0
                                to: 0
                                duration: 1
                                easing.type: Easing.Linear
                            }

                            ScriptAction {
                                script: {
                                    win.didFirstScroll = true

                                    let newText = scrollText.getSongDisplayText()
                                    if (scrollText.text !== newText) {
                                        scrollText.text = newText
                                        scrollText.x = clipRect.width

                                        if (scrollText.width < clipRect.width) {
                                            loopShortAnim.start()
                                        } else {
                                            loopLongAnim.start()
                                        }
                                    } else {
                                        loopStaticAnim.start()
                                    }
                                }
                            }
                        }

                        SequentialAnimation on x {
                            id: firstLongAnim
                            running: false

                            NumberAnimation {
                                from: 0
                                to: -scrollText.width
                                duration: (scrollText.width + clipRect.width) * horizontalScrollPeriod

                                easing.type: Easing.Linear
                            }

                            ScriptAction {
                                script: {
                                    win.didFirstScroll = true

                                    let newText = scrollText.getSongDisplayText()
                                    if (scrollText.text !== newText) {
                                        scrollText.text = newText
                                        scrollText.x = clipRect.width

                                        if (scrollText.width < clipRect.width) {
                                            loopShortAnim.start()
                                        } else {
                                            loopLongAnim.start()
                                        }
                                    } else {
                                        loopLongAnim.start()
                                    }
                                }
                            }
                        }

                        SequentialAnimation on x {
                            id: loopLongAnim
                            running: false
                            loops: Animation.Infinite

                            NumberAnimation {
                                from: clipRect.width
                                to: -scrollText.width
                                duration: (scrollText.width + clipRect.width) * horizontalScrollPeriod

                                easing.type: Easing.Linear
                            }

                            ScriptAction {
                                script: {
                                    let newText = scrollText.getSongDisplayText()
                                    if (scrollText.text !== newText) {
                                        scrollText.text = newText
                                        scrollText.x = clipRect.width

                                        if (scrollText.width < clipRect.width) {
                                            this.stop()
                                            loopShortAnim.start()
                                        } else {
                                            loopLongAnim.start()
                                        }
                                    } else {
                                        loopLongAnim.start()
                                    }
                                }
                            }
                        }

                        SequentialAnimation on x {
                            id: loopShortAnim
                            running: false

                            NumberAnimation {
                                from: clipRect.width
                                to: 0
                                duration: clipRect.width * horizontalScrollPeriod

                                easing.type: Easing.Linear
                            }

                            ScriptAction {
                                script: {
                                    let newText = scrollText.getSongDisplayText()
                                    if (scrollText.text !== newText) {
                                        shortExitAnim.start()
                                    } else {
                                        loopStaticAnim.start()
                                    }
                                }
                            }
                        }

                        SequentialAnimation on x {
                            id: loopStaticAnim
                            running: false
                            loops: Animation.Infinite

                            NumberAnimation {
                                from: 0
                                to: 0
                                duration: 1000

                                easing.type: Easing.Linear
                            }

                            ScriptAction {
                                script: {
                                    let newText = scrollText.getSongDisplayText()
                                    if (scrollText.text !== newText) {
                                        loopStaticAnim.stop()
                                        shortExitAnim.start()
                                    }
                                }
                            }
                        }

                        SequentialAnimation on x {
                            id: shortExitAnim
                            running: false

                            NumberAnimation {
                                from: 0
                                to: -scrollText.width
                                duration: scrollText.width * horizontalScrollPeriod

                                easing.type: Easing.Linear
                            }

                            ScriptAction {
                                script: {
                                    let newText = scrollText.getSongDisplayText()
                                    scrollText.text = newText
                                    scrollText.x = clipRect.width
                                    if (scrollText.width > clipRect.width) {
                                        loopLongAnim.start()
                                    } else {
                                        loopShortAnim.start()
                                    }
                                }
                            }
                        }

                        Component.onCompleted: {
                            scrollText.text = scrollText.getSongDisplayText()
                            scrollText.x = 0

                            if (!win.didFirstScroll) {
                                if (scrollText.width > clipRect.width) {
                                    firstLongAnim.start()
                                } else {
                                    firstShortAnim.start()
                                }
                            } else {
                                if (scrollText.width > clipRect.width) {
                                    loopLongAnim.start()
                                } else {
                                    loopShortAnim.start()
                                }
                            }
                        }
                    }
                }
            }

            Rectangle {
                color: "transparent"

                Layout.fillWidth: true
                Layout.fillHeight: true

                RowLayout {
                    anchors.fill: parent

                    spacing: 10

                    Text {
                        id: curTime

                        text: {
                            if (mediaViewModel) {
                                let totalSeconds = Math.floor(mediaViewModel.currentTimeRaw / 1000)
                                let minutes = Math.floor(totalSeconds / 60)
                                let seconds = totalSeconds % 60

                                return qsTr("%1:%2")
                                    .arg(minutes < 10 ? "0" + minutes : minutes)
                                    .arg(seconds < 10 ? "0" + seconds : seconds)
                            }

                            return ""
                        }

                        font.pixelSize: 18
                        font.family: encodeSansThin.name
                        font.weight: Font.Thin

                        color: "#000000"

                        renderType: Text.NativeRendering

                        Layout.preferredWidth: 40
                        Layout.fillHeight: true

                        verticalAlignment: Text.AlignVCenter
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        color: "transparent"

                        Slider {
                            id: timeSlider

                            width: 110

                            value: mediaViewModel && mediaViewModel.getCurrentDurationRaw() > 0 ?
                                        mediaViewModel.currentTimeRaw / mediaViewModel.getCurrentDurationRaw() :
                                        0

                            anchors.verticalCenter: parent.verticalCenter

                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                            MouseArea {
                                anchors.fill: parent

                                acceptedButtons: Qt.AllButtons
                            }

                            handle: Rectangle {
                                width: 10
                                height: 10

                                radius: width / 2

                                color: "#000000"

                                border.color: "#ffffff"
                                border.width: 1

                                x: timeSlider.leftPadding + timeSlider.visualPosition * (timeSlider.availableWidth - width)
                                y: (parent.height - height) / 2
                            }
                        }
                    }
                }
            }
        }
    }
}
