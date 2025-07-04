import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtScxml

ApplicationWindow {
    id: editorWindow
    title: "ARHUD Editor"
    objectName: "editorWindow"

    visible: true

    width: 600
    height: 650

    x: 900
    y: 100

    color: "#ffffc5"

    property int selectedTempUnit: 0
    property int selectedWindUnit: 0
    property bool initialLoadDone: false

    property int currentState: errorManagerEditor.currentState

    Component.onCompleted: {
        selectedTempUnit = weatherViewModel.getCurrentTemperatureUnitRaw()
        selectedWindUnit = weatherViewModel.getCurrentWindSpeedUnitRaw()

        tempUnitCombo.currentIndex = selectedTempUnit
        windUnitCombo.currentIndex = selectedWindUnit

        curProvinceCombo.currentIndex = weatherViewModel.getCurrentProvinceRaw()
        curConditionCombo.currentIndex = weatherViewModel.getCurrentConditionRaw()
        destProvinceCombo.currentIndex = weatherViewModel.getDestinationProvinceRaw()
        destConditionCombo.currentIndex = weatherViewModel.getDestinationConditionRaw()

        initialLoadDone = true
    }

    ScrollView {
        anchors.fill: parent
        anchors.margins: 16

        Item {
            width: parent.width - 16
            implicitHeight: column.implicitHeight

            ColumnLayout {
                id: column
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 16

                RowLayout {
                    spacing: 24

                    ComboBox {
                        id: tempUnitCombo
                        Layout.fillWidth: true
                        model: ["Celsius (°C)", "Fahrenheit (°F)", "Kelvin (K)"]
                        currentIndex: selectedTempUnit

                        onCurrentIndexChanged: {
                            if (initialLoadDone) {
                                selectedTempUnit = currentIndex
                                weatherViewModel.setCurrentTemperatureUnit(currentIndex)
                                weatherViewModel.setDestinationTemperatureUnit(currentIndex)
                            }
                        }
                    }

                    ComboBox {
                        id: windUnitCombo
                        Layout.fillWidth: true
                        model: ["m/s", "km/h", "mph"]
                        currentIndex: selectedWindUnit

                        onCurrentIndexChanged: {
                            if (initialLoadDone) {
                                selectedWindUnit = currentIndex
                                weatherViewModel.setCurrentWindSpeedUnit(currentIndex)
                                weatherViewModel.setDestinationWindSpeedUnit(currentIndex)
                            }
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 24

                    GroupBox {
                        title: "Current Weather"
                        Layout.fillWidth: true

                        ColumnLayout {
                            spacing: 6

                            ComboBox {
                                id: curProvinceCombo
                                Layout.fillWidth: true
                                model: [
                                    "0 - An Giang", "1 - Bac Ninh", "2 - Ca Mau", "3 - Can Tho",
                                    "4 - Cao Bang", "5 - Dak Lak", "6 - Da Nang", "7 - Dien Bien",
                                    "8 - Dong Nai", "9 - Dong Thap", "10 - Gia Lai", "11 - Hai Phong",
                                    "12 - Ha Noi", "13 - Ha Tinh", "14 - Ho Chi Minh", "15 - Hue",
                                    "16 - Hung Yen", "17 - Khanh Hoa", "18 - Lai Chau", "19 - Lam Dong",
                                    "20 - Lang Son", "21 - Lao Cai", "22 - Nghe An", "23 - Ninh Binh",
                                    "24 - Phu Tho", "25 - Quang Ngai", "26 - Quang Ninh", "27 - Quang Tri",
                                    "28 - Son La", "29 - Tay Ninh", "30 - Thai Nguyen", "31 - Thanh Hoa",
                                    "32 - Tuyen Quang", "33 - Vinh Long"
                                ]

                                onCurrentIndexChanged: {
                                    if (initialLoadDone)
                                        weatherViewModel.setCurrentProvinceName(currentIndex)
                                }
                            }

                            TextField {
                                placeholderText: "Temperature"
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: weatherViewModel ? weatherViewModel.currentTemperature : ""
                                onEditingFinished: weatherViewModel.setCurrentTemperature(parseInt(text))
                            }

                            ComboBox {
                                id: curConditionCombo
                                Layout.fillWidth: true
                                model: ["Cloudy", "Foggy", "Partly Cloudy", "Rainy", "Stormy", "Sunny"]

                                onCurrentIndexChanged: {
                                    if (initialLoadDone)
                                        weatherViewModel.setCurrentCondition(currentIndex)
                                }
                            }

                            TextField {
                                placeholderText: "Wind Speed"
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: weatherViewModel ? weatherViewModel.currentWindSpeed : ""
                                onEditingFinished: weatherViewModel.setCurrentWindSpeed(parseInt(text))
                            }
                        }
                    }

                    GroupBox {
                        title: "Destination Weather"
                        Layout.fillWidth: true

                        ColumnLayout {
                            spacing: 6

                            ComboBox {
                                id: destProvinceCombo
                                Layout.fillWidth: true
                                model: curProvinceCombo.model

                                onCurrentIndexChanged: {
                                    if (initialLoadDone)
                                        weatherViewModel.setDestinationProvinceName(currentIndex)
                                }
                            }

                            TextField {
                                placeholderText: "Temperature"
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: weatherViewModel ? weatherViewModel.destinationTemperature : ""
                                onEditingFinished: weatherViewModel.setDestinationTemperature(parseInt(text))
                            }

                            ComboBox {
                                id: destConditionCombo
                                Layout.fillWidth: true
                                model: curConditionCombo.model

                                onCurrentIndexChanged: {
                                    if (initialLoadDone)
                                        weatherViewModel.setDestinationCondition(currentIndex)
                                }
                            }

                            TextField {
                                placeholderText: "Wind Speed"
                                inputMethodHints: Qt.ImhDigitsOnly
                                text: weatherViewModel ? weatherViewModel.destinationWindSpeed : ""
                                onEditingFinished: weatherViewModel.setDestinationWindSpeed(parseInt(text))
                            }
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 24

                        GroupBox {
                            title: "Current Media"
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1

                            ColumnLayout {
                                spacing: 6

                                Label {
                                    text: `Source: ${mediaViewModel ? mediaViewModel.currentSource : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Album: ${mediaViewModel ? mediaViewModel.currentAlbum : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Artist: ${mediaViewModel ? mediaViewModel.currentArtist : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Song: ${mediaViewModel ? mediaViewModel.currentSong : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Duration (ms): ${mediaViewModel ? mediaViewModel.currentDuration : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Elapsed Time (ms): ${mediaViewModel ? mediaViewModel.currentTime : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }
                        }

                        GroupBox {
                            title: "Next Media"
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1

                            ColumnLayout {
                                spacing: 6

                                Label {
                                    text: `Source: ${mediaViewModel ? mediaViewModel.nextSource : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Album: ${mediaViewModel ? mediaViewModel.nextAlbum : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Artist: ${mediaViewModel ? mediaViewModel.nextArtist : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Song: ${mediaViewModel ? mediaViewModel.nextSong : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Duration (ms): ${mediaViewModel ? mediaViewModel.nextDuration : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                                Label {
                                    text: `Elapsed Time (ms): ${mediaViewModel ? mediaViewModel.nextTime : ""}`
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12

                        ComboBox {
                            id: nextSong
                            Layout.fillWidth: true
                            model: mediaViewModel ? mediaViewModel.songDisplayList : ""

                            onCurrentIndexChanged: {
                                if (mediaViewModel) {
                                    let song = mediaViewModel.getSongObject(currentIndex)

                                    mediaViewModel.setNextMedia(
                                        song.source,
                                        song.album,
                                        song.artist,
                                        song.song,
                                        song.duration,
                                        0
                                    )
                                }
                            }
                        }

                        Button {
                            text: "Skip to Next"
                            onClicked: {
                                mediaViewModel.setCurrentMedia(
                                    mediaViewModel.getNextSourceRaw(),
                                    mediaViewModel.nextAlbum,
                                    mediaViewModel.nextArtist,
                                    mediaViewModel.nextSong,
                                    mediaViewModel.getNextDurationRaw(),
                                    0
                                )

                                nextSong.currentIndex = 0
                            }
                        }
                    }
                }

                GroupBox {
                    id: errorManagerEditor
                    title: "Error Manager"

                    Layout.fillWidth: true

                    property int currentState: 0  // 0 = No Error, 1 = NoDisplay Error
                    property bool onEventSignal: true
                    property bool periodicSignal: true
                    property int periodicCurrentTime: 0
                    property int periodicTotalTime: 10
                    property int reconnectingTime: 0
                    property int reconnectingTotalTime: 5
                    property bool reconnectingActive: false
                    property bool isConnecting: true
                    property int isConnectingTime: 0
                    property int isConnectingTotalTime: 18
                    property string displayMessage: "System operating normally."

                    Timer {
                        interval: 1000
                        repeat: true
                        running: true
                        onTriggered: {
                            errorManagerEditor.isConnectingTime += 1

                            if (errorManagerEditor.isConnectingTime >= errorManagerEditor.isConnectingTotalTime) {
                                errorManagerEditor.isConnecting = !errorManagerEditor.isConnecting
                                errorManagerEditor.isConnectingTime = 0

                                if (errorManagerEditor.isConnecting) {
                                    errorManagerEditor.periodicSignal = true
                                    errorManagerEditor.periodicCurrentTime = 0
                                    errorManagerEditor.reconnectingTime = 0
                                    errorManagerEditor.reconnectingActive = false
                                    errorManagerEditor.currentState = 0
                                    errorManagerEditor.displayMessage = "System operating normally."
                                }
                            }

                            if (!errorManagerEditor.reconnectingActive) {
                                errorManagerEditor.periodicCurrentTime += 1

                                if (errorManagerEditor.periodicCurrentTime >= errorManagerEditor.periodicTotalTime) {
                                    if (errorManagerEditor.isConnecting) {
                                        errorManagerEditor.periodicCurrentTime = 0
                                    } else {
                                        errorManagerEditor.reconnectingActive = true
                                        errorManagerEditor.reconnectingTime = 0
                                    }
                                }
                            } else {
                                errorManagerEditor.reconnectingTime += 1

                                if (errorManagerEditor.isConnecting) {
                                    errorManagerEditor.reconnectingActive = false
                                    errorManagerEditor.periodicCurrentTime = 0
                                    errorManagerEditor.reconnectingTime = 0
                                } else if (errorManagerEditor.reconnectingTime >= errorManagerEditor.reconnectingTotalTime) {
                                    errorManagerEditor.periodicSignal = false
                                    errorManagerEditor.reconnectingTime = 0
                                    errorManagerEditor.currentState = 1
                                    errorManagerEditor.displayMessage = "[NoDisplay Error] Periodic signal timeout. Elapsed time exceeded maximum limit of 10 seconds. Possible connection issue or unresponsive module detected. Please check system status."
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 6
                        Layout.fillWidth: true

                        Label {
                            text: `State: ${errorManagerEditor.currentState === 0 ? "No Error" : "NoDisplay Error"}`
                        }

                        Item {
                            width: parent.width
                            height: checkbox1.implicitHeight

                            Label {
                                id: outOfRangeLabel
                                text: "OnEvent Signal:"
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            CheckBox {
                                id: checkbox1
                                checked: errorManagerEditor.onEventSignal
                                anchors.left: outOfRangeLabel.right
                                anchors.leftMargin: 6
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.verticalCenterOffset: 2

                                MouseArea {
                                    anchors.fill: parent
                                    acceptedButtons: Qt.AllButtons
                                }
                            }
                        }

                        Item {
                            width: parent.width
                            height: checkbox2.implicitHeight

                            Label {
                                id: periodicLabel
                                text: "Periodic Signal:"
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            CheckBox {
                                id: checkbox2
                                checked: errorManagerEditor.periodicSignal
                                anchors.left: periodicLabel.right
                                anchors.leftMargin: 6
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.verticalCenterOffset: 2

                                MouseArea {
                                    anchors.fill: parent
                                    acceptedButtons: Qt.AllButtons
                                }
                            }
                        }

                        Label {
                            text: `Checking Timer: ${errorManagerEditor.periodicCurrentTime} / ${errorManagerEditor.periodicTotalTime} (s)`
                        }

                        Label {
                            text: `Reconnecting Timer: ${errorManagerEditor.reconnectingTime} / ${errorManagerEditor.reconnectingTotalTime} (s)`
                        }

                        Label {
                            text: `Is Connecting Timer: ${errorManagerEditor.isConnectingTime} / ${errorManagerEditor.isConnectingTotalTime} (s)`
                        }

                        Label {
                            text: `Is Connecting: ${errorManagerEditor.isConnecting ? "True" : "False"}`
                        }

                        Rectangle {
                            color: "transparent"
                            radius: 4
                            width: errorManagerEditor.width - 20
                            height: textBlock.implicitHeight + 12

                            Text {
                                id: textBlock
                                textFormat: Text.RichText
                                wrapMode: Text.Wrap
                                anchors.fill: parent

                                text: {
                                    if (errorManagerEditor.currentState === 0) {
                                        return `<font color='green'>[No Error]</font> System operating normally.`
                                    } else {
                                        let msg = errorManagerEditor.displayMessage
                                        let openBracket = msg.indexOf('[')
                                        let closeBracket = msg.indexOf(']') + 1

                                        if (openBracket !== -1 && closeBracket > openBracket) {
                                            let before = msg.substring(0, openBracket)
                                            let bracket = msg.substring(openBracket, closeBracket)
                                            let after = msg.substring(closeBracket)
                                            return `${before}<font color='red'>${bracket}</font>${after}`
                                        } else {
                                            return msg
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                GroupBox {
                    title: "Streaming Data"
                    Layout.fillWidth: true

                    ColumnLayout {
                        width: parent.width
                        spacing: 6

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 4

                            Text {
                                text: "Input Path:"
                            }

                            Text {
                                id: inputPathText
                                text: streamingViewModel ? streamingViewModel.inputPath : ""
                                elide: Text.ElideLeft
                                wrapMode: Text.NoWrap
                                Layout.fillWidth: true
                                horizontalAlignment: Text.AlignLeft

                                TextMetrics {
                                    id: inputPathMetrics
                                    text: inputPathText.text
                                    font: inputPathText.font
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true

                                    ToolTip.visible: containsMouse && inputPathMetrics.width > inputPathText.width
                                    ToolTip.text: streamingViewModel ? streamingViewModel.inputPath : ""
                                }
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 4

                            Text {
                                text: "Output Path:"
                            }

                            Text {
                                id: outputPathText
                                text: streamingViewModel ? streamingViewModel.outputPath : ""
                                elide: Text.ElideLeft
                                wrapMode: Text.NoWrap
                                Layout.fillWidth: true
                                horizontalAlignment: Text.AlignLeft

                                TextMetrics {
                                    id: outputPathMetrics
                                    text: outputPathText.text
                                    font: outputPathText.font
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true

                                    ToolTip.visible: containsMouse && outputPathMetrics.width > outputPathText.width
                                    ToolTip.text: streamingViewModel ? streamingViewModel.outputPath : ""
                                }
                            }
                        }

                        RowLayout {
                            id: outRow
                            Layout.fillWidth: true
                            spacing: 24

                            ColumnLayout {
                                spacing: 4
                                Label { text: "Video Properties:"; font.bold: true }
                                Label { text: `Width: ${streamingViewModel ? streamingViewModel.videoWidth : 0}` }
                                Label { text: `Height: ${streamingViewModel ? streamingViewModel.videoHeight : 0}` }
                                Label { text: `Ratio: ${streamingViewModel ? outRow.approximateRatio(streamingViewModel.videoRatio) : 0}` }
                                Label { text: `FPS: ${streamingViewModel ? streamingViewModel.frameRate : 0}` }
                            }

                            ColumnLayout {
                                spacing: 4
                                Label { text: "Source Properties:"; font.bold: true }
                                Label { text: `Width: ${streamingViewModel ? streamingViewModel.sourceWidth : 0}` }
                                Label { text: `Height: ${streamingViewModel ? streamingViewModel.sourceHeight : 0}` }
                                Label { text: `Ratio: ${streamingViewModel ? outRow.approximateRatio(streamingViewModel.sourceRatio) : 0}` }
                                Label { text: `FPS: ${streamingViewModel ? streamingViewModel.sourceFPS : 0}` }
                            }

                            function approximateRatio(ratio) {
                                if (ratio <= 0) return "Unknown";

                                var knownRatios = [
                                    { r: 16/9, label: "16:9" },
                                    { r: 4/3, label: "4:3" },
                                    { r: 21/9, label: "21:9" },
                                    { r: 3/2, label: "3:2" },
                                    { r: 1, label: "1:1" }
                                ];

                                for (var i = 0; i < knownRatios.length; ++i) {
                                    if (Math.abs(ratio - knownRatios[i].r) < 0.05)
                                        return knownRatios[i].label;
                                }

                                var y = 1;
                                var x = Math.round(ratio * y);
                                while (x < 100 && Math.abs(x/y - ratio) > 0.01) {
                                    y++;
                                    x = Math.round(ratio * y);
                                }
                                return x + ":" + y;
                            }
                        }

                        Item {
                            width: parent.width
                            height: ratioCheckbox.implicitHeight

                            Label {
                                id: ratioLabel
                                text: "Const Ratio:"
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            CheckBox {
                                id: ratioCheckbox
                                checked: streamingViewModel ? streamingViewModel.isRatioConst : false
                                anchors.left: ratioLabel.right
                                anchors.leftMargin: 6
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.verticalCenterOffset: 2
                                MouseArea { anchors.fill: parent; acceptedButtons: Qt.AllButtons }
                            }
                        }

                        Item {
                            width: parent.width
                            height: streamingCheckbox.implicitHeight

                            Label {
                                id: streamingLabel
                                text: "Streaming:"
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            CheckBox {
                                id: streamingCheckbox
                                checked: streamingViewModel ? streamingViewModel.isStreaming : false
                                anchors.left: streamingLabel.right
                                anchors.leftMargin: 6
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.verticalCenterOffset: 2
                                MouseArea { anchors.fill: parent; acceptedButtons: Qt.AllButtons }
                            }
                        }
                    }
                }
            }
        }
    }
}
