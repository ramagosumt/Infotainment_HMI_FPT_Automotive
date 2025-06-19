import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: editorWindow
    title: "Weather Editor"
    visible: true
    width: 600
    height: 400
    x: 900
    y: 200

    color: "#ffffc5"

    property int selectedTempUnit: 0
    property int selectedWindUnit: 0
    property bool initialLoadDone: false

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

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
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
    }
}
