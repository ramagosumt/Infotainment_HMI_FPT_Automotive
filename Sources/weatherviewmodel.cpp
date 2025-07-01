#include "weatherviewmodel.h"

WeatherViewModel::WeatherViewModel(QObject *parent)
    : QObject{parent}, weatherModel(new WeatherModel(this)), m_ownsModel(true)
{}

WeatherViewModel::WeatherViewModel(WeatherModel* model, QObject *parent)
    : QObject(parent), weatherModel(model)
{}

WeatherViewModel::~WeatherViewModel() {
    if (m_ownsModel && weatherModel) delete weatherModel;
}

QString WeatherViewModel::getCurrentProvinceName() const {
    return convertProvinceToString(weatherModel->getCurrentProvinceName());
}

QString WeatherViewModel::getCurrentTemperature() const {
    return QString::number(weatherModel->getCurrentTemperature());
}

QString WeatherViewModel::getCurrentTemperatureUnit() const {
    return convertTemperatureUnitToString(weatherModel->getCurrentTemperatureUnit());
}

QString WeatherViewModel::getCurrentCondition() const {
    return convertConditionToString(weatherModel->getCurrentCondition());
}

QString WeatherViewModel::getCurrentWindSpeed() const {
    return QString::number(weatherModel->getCurrentWindSpeed());
}

QString WeatherViewModel::getCurrentWindSpeedUnit() const {
    return convertWindSpeedUnitToString(weatherModel->getCurrentWindSpeedUnit());
}

QString WeatherViewModel::getDestinationProvinceName() const {
    return convertProvinceToString(weatherModel->getDestinationProvinceName());
}

QString WeatherViewModel::getDestinationTemperature() const {
    return QString::number(weatherModel->getDestinationTemperature());
}

QString WeatherViewModel::getDestinationTemperatureUnit() const {
    return convertTemperatureUnitToString(weatherModel->getDestinationTemperatureUnit());
}

QString WeatherViewModel::getDestinationCondition() const {
    return convertConditionToString(weatherModel->getDestinationCondition());
}

QString WeatherViewModel::getDestinationWindSpeed() const {
    return QString::number(weatherModel->getDestinationWindSpeed());
}

QString WeatherViewModel::getDestinationWindSpeedUnit() const {
    return convertWindSpeedUnitToString(weatherModel->getDestinationWindSpeedUnit());
}

qint8 WeatherViewModel::getCurrentProvinceRaw() const {
    return weatherModel->getCurrentProvinceName();
}

qint16 WeatherViewModel::getCurrentTemperatureRaw() const {
    return weatherModel->getCurrentTemperature();
}

qint8 WeatherViewModel::getCurrentTemperatureUnitRaw() const {
    return weatherModel->getCurrentTemperatureUnit();
}

qint8 WeatherViewModel::getCurrentConditionRaw() const {
    return weatherModel->getCurrentCondition();
}

qint16 WeatherViewModel::getCurrentWindSpeedRaw() const {
    return weatherModel->getCurrentWindSpeed();
}

qint8 WeatherViewModel::getCurrentWindSpeedUnitRaw() const {
    return weatherModel->getCurrentWindSpeedUnit();
}

qint8 WeatherViewModel::getDestinationProvinceRaw() const {
    return weatherModel->getDestinationProvinceName();
}

qint16 WeatherViewModel::getDestinationTemperatureRaw() const {
    return weatherModel->getDestinationTemperature();
}

qint8 WeatherViewModel::getDestinationTemperatureUnitRaw() const {
    return weatherModel->getDestinationTemperatureUnit();
}

qint8 WeatherViewModel::getDestinationConditionRaw() const {
    return weatherModel->getDestinationCondition();
}

qint16 WeatherViewModel::getDestinationWindSpeedRaw() const {
    return weatherModel->getDestinationWindSpeed();
}

qint8 WeatherViewModel::getDestinationWindSpeedUnitRaw() const {
    return weatherModel->getDestinationWindSpeedUnit();
}

QString WeatherViewModel::getCurrentConditionIcon() const {
    switch (weatherModel->getCurrentCondition()) {
    case WeatherModel::CLOUDY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Cloudy100.png";
    case WeatherModel::FOGGY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Foggy100.png";
    case WeatherModel::PARTLYCLOUDY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/PartlyCloudy100.png";
    case WeatherModel::RAINY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Rainy100.png";
    case WeatherModel::STORMY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Stormy100.png";
    case WeatherModel::SUNNY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Sunny100.png";
    default:
        return "Unknown";
    }
}

QString WeatherViewModel::getDestinationConditionIcon() const {
    switch (weatherModel->getDestinationCondition()) {
    case WeatherModel::CLOUDY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Cloudy100.png";
    case WeatherModel::FOGGY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Foggy100.png";
    case WeatherModel::PARTLYCLOUDY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/PartlyCloudy100.png";
    case WeatherModel::RAINY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Rainy100.png";
    case WeatherModel::STORMY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Stormy100.png";
    case WeatherModel::SUNNY:
        return "qrc:/WeatherApp_MVVM/assets/images/weather/Sunny100.png";
    default:
        return "Unknown";
    }
}

void WeatherViewModel::setCurrentProvinceName(const qint8 id) {
    if (id == weatherModel->getCurrentProvinceName()) return;
    weatherModel->setCurrentProvinceName(id);
    emit onCurrentProvinceNameChanged();
}

void WeatherViewModel::setCurrentTemperature(const qint16 temperature) {
    if (temperature == weatherModel->getCurrentTemperature()) return;
    weatherModel->setCurrentTemperature(temperature);
    emit onCurrentTemperatureChanged();
}

void WeatherViewModel::setCurrentTemperatureUnit(const qint8 unit) {
    qint8 oldUnit = weatherModel->getCurrentTemperatureUnit();
    if (unit == oldUnit) return;

    qint8 temp = weatherModel->getCurrentTemperature();
    if (oldUnit == 1) temp = WeatherModel::convertFahrenheitToCelsius(temp);
    else if (oldUnit == 2) temp = WeatherModel::convertKelvinToCelsius(temp);
    if (unit == 1) temp = WeatherModel::convertCelsiusToFahrenheit(temp);
    else if (unit == 2) temp = WeatherModel::convertCelsiusToKelvin(temp);

    weatherModel->setCurrentTemperature(temp);
    weatherModel->setCurrentTemperatureUnit(unit);

    emit onCurrentTemperatureUnitChanged();
    emit onCurrentTemperatureChanged();
}

void WeatherViewModel::setCurrentCondition(const qint8 condition) {
    if (condition == weatherModel->getCurrentCondition()) return;
    weatherModel->setCurrentCondition(condition);
    emit onCurrentConditionChanged();
    emit onCurrentConditionIconChanged();
}

void WeatherViewModel::setCurrentWindSpeed(const qint16 windspeed) {
    if (windspeed == weatherModel->getCurrentWindSpeed()) return;
    weatherModel->setCurrentWindSpeed(windspeed);
    emit onCurrentWindSpeedChanged();
}

void WeatherViewModel::setCurrentWindSpeedUnit(const qint8 unit) {
    qint8 oldUnit = weatherModel->getCurrentWindSpeedUnit();
    if (unit == oldUnit) return;

    qint8 speed = weatherModel->getCurrentWindSpeed();
    if (oldUnit == 1) speed = static_cast<qint8>(speed / 3.6f + 0.5f);
    else if (oldUnit == 2) speed = static_cast<qint8>(speed / 2.23694f + 0.5f);
    if (unit == 1) speed = WeatherModel::convertMetersPerSecondToKilometersPerHour(speed);
    else if (unit == 2) speed = WeatherModel::convertMetersPerSecondToMilesPerHour(speed);

    weatherModel->setCurrentWindSpeed(speed);
    weatherModel->setCurrentWindSpeedUnit(unit);

    emit onCurrentWindSpeedUnitChanged();
    emit onCurrentWindSpeedChanged();
}

void WeatherViewModel::setDestinationProvinceName(const qint8 id) {
    if (id == weatherModel->getDestinationProvinceName()) return;
    weatherModel->setDestinationProvinceName(id);
    emit onDestinationProvinceNameChanged();
}

void WeatherViewModel::setDestinationTemperature(const qint16 temperature) {
    if (temperature == weatherModel->getDestinationTemperature()) return;
    weatherModel->setDestinationTemperature(temperature);
    emit onDestinationTemperatureChanged();
}

void WeatherViewModel::setDestinationTemperatureUnit(const qint8 unit) {
    qint8 oldUnit = weatherModel->getDestinationTemperatureUnit();
    if (unit == oldUnit) return;

    qint8 temp = weatherModel->getDestinationTemperature();
    if (oldUnit == 1) temp = WeatherModel::convertFahrenheitToCelsius(temp);
    else if (oldUnit == 2) temp = WeatherModel::convertKelvinToCelsius(temp);
    if (unit == 1) temp = WeatherModel::convertCelsiusToFahrenheit(temp);
    else if (unit == 2) temp = WeatherModel::convertCelsiusToKelvin(temp);

    weatherModel->setDestinationTemperature(temp);
    weatherModel->setDestinationTemperatureUnit(unit);

    emit onDestinationTemperatureUnitChanged();
    emit onDestinationTemperatureChanged();
}

void WeatherViewModel::setDestinationCondition(const qint8 condition) {
    if (condition == weatherModel->getDestinationCondition()) return;
    weatherModel->setDestinationCondition(condition);
    emit onDestinationConditionChanged();
    emit onDestinationConditionIconChanged();
}

void WeatherViewModel::setDestinationWindSpeed(const qint16 windspeed) {
    if (windspeed == weatherModel->getDestinationWindSpeed()) return;
    weatherModel->setDestinationWindSpeed(windspeed);
    emit onDestinationWindSpeedChanged();
}

void WeatherViewModel::setDestinationWindSpeedUnit(const qint8 unit) {
    qint8 oldUnit = weatherModel->getDestinationWindSpeedUnit();
    if (unit == oldUnit) return;

    qint8 speed = weatherModel->getDestinationWindSpeed();
    if (oldUnit == 1) speed = static_cast<qint8>(speed / 3.6f + 0.5f);
    else if (oldUnit == 2) speed = static_cast<qint8>(speed / 2.23694f + 0.5f);
    if (unit == 1) speed = WeatherModel::convertMetersPerSecondToKilometersPerHour(speed);
    else if (unit == 2) speed = WeatherModel::convertMetersPerSecondToMilesPerHour(speed);

    weatherModel->setDestinationWindSpeed(speed);
    weatherModel->setDestinationWindSpeedUnit(unit);

    emit onDestinationWindSpeedUnitChanged();
    emit onDestinationWindSpeedChanged();
}

QString WeatherViewModel::convertProvinceToString(qint8 id) const {
    switch (id) {
    case 0: return "An Giang";
    case 1: return "Bac Ninh";
    case 2: return "Ca Mau";
    case 3: return "Can Tho";
    case 4: return "Cao Bang";
    case 5: return "Dak Lak";
    case 6: return "Da Nang";
    case 7: return "Dien Bien";
    case 8: return "Dong Nai";
    case 9: return "Dong Thap";
    case 10: return "Gia Lai";
    case 11: return "Hai Phong";
    case 12: return "Ha Noi";
    case 13: return "Ha Tinh";
    case 14: return "Ho Chi Minh";
    case 15: return "Hue";
    case 16: return "Hung Yen";
    case 17: return "Khanh Hoa";
    case 18: return "Lai Chau";
    case 19: return "Lam Dong";
    case 20: return "Lang Son";
    case 21: return "Lao Cai";
    case 22: return "Nghe An";
    case 23: return "Ninh Binh";
    case 24: return "Phu Tho";
    case 25: return "Quang Ngai";
    case 26: return "Quang Ninh";
    case 27: return "Quang Tri";
    case 28: return "Son La";
    case 29: return "Tay Ninh";
    case 30: return "Thai Nguyen";
    case 31: return "Thanh Hoa";
    case 32: return "Tuyen Quang";
    case 33: return "Vinh Long";
    default: return "Unknown";
    }
}

QString WeatherViewModel::convertTemperatureUnitToString(qint8 unit) const {
    switch (unit) {
    case 0: return "°C";
    case 1: return "°F";
    case 2: return "K";
    default: return "Unknown";
    }
}

QString WeatherViewModel::convertConditionToString(qint8 condition) const {
    switch (condition) {
    case 0: return "Cloudy";
    case 1: return "Foggy";
    case 2: return "Partly Cloudy";
    case 3: return "Rainy";
    case 4: return "Stormy";
    case 5: return "Sunny";
    default: return "Unknown";
    }
}

QString WeatherViewModel::convertWindSpeedUnitToString(qint8 unit) const {
    switch (unit) {
    case 0: return "m/s";
    case 1: return "km/h";
    case 2: return "mph";
    default: return "Unknown";
    }
}
