#include "Weather/weathermodel.h"

WeatherModel::WeatherModel(QObject *parent)
    : QObject{parent}
{
    m_current.province = HANOI;
    m_current.temperature = 20;
    m_current.temperatureUnit = DEGREE;
    m_current.condition = SUNNY;
    m_current.windSpeed = 5;
    m_current.windSpeedUnit = METERSPERSECOND;

    m_destination.province = THANHHOA;
    m_destination.temperature = 25;
    m_destination.temperatureUnit = DEGREE;
    m_destination.condition = RAINY;
    m_destination.windSpeed = 1;
    m_destination.windSpeedUnit = METERSPERSECOND;
}

qint8 WeatherModel::getCurrentProvinceName() const {
    return static_cast<qint8>(m_current.province);
}

qint16 WeatherModel::getCurrentTemperature() const {
    return m_current.temperature;
}

qint8 WeatherModel::getCurrentTemperatureUnit() const {
    return static_cast<qint8>(m_current.temperatureUnit);
}

qint8 WeatherModel::getCurrentCondition() const {
    return static_cast<qint8>(m_current.condition);
}

qint16 WeatherModel::getCurrentWindSpeed() const {
    return m_current.windSpeed;
}

qint8 WeatherModel::getCurrentWindSpeedUnit() const {
    return static_cast<qint8>(m_current.windSpeedUnit);
}

qint8 WeatherModel::getDestinationProvinceName() const {
    return static_cast<qint8>(m_destination.province);
}

qint16 WeatherModel::getDestinationTemperature() const {
    return m_destination.temperature;
}

qint8 WeatherModel::getDestinationTemperatureUnit() const {
    return static_cast<qint8>(m_destination.temperatureUnit);
}

qint8 WeatherModel::getDestinationCondition() const {
    return static_cast<qint8>(m_destination.condition);
}

qint16 WeatherModel::getDestinationWindSpeed() const {
    return m_destination.windSpeed;
}

qint8 WeatherModel::getDestinationWindSpeedUnit() const {
    return static_cast<qint8>(m_destination.windSpeedUnit);
}

void WeatherModel::setCurrentProvinceName(const qint8 id) {
    if (id < ANGIANG || id > VINHLONG) return;

    auto newProvince = static_cast<Province>(id);
    if (m_current.province != newProvince) m_current.province = newProvince;
}

void WeatherModel::setCurrentTemperature(const qint16 temperature) {
    if (m_current.temperature != temperature) m_current.temperature = temperature;
}

void WeatherModel::setCurrentTemperatureUnit(const qint8 unit) {
    if (unit < DEGREE || unit > KELVIN) return;

    auto newUnit = static_cast<TemperatureUnit>(unit);
    if (m_current.temperatureUnit != newUnit) m_current.temperatureUnit = newUnit;
}

void WeatherModel::setCurrentCondition(const qint8 condition) {
    auto newCondition = static_cast<Condition>(condition);
    if (m_current.condition != newCondition) m_current.condition = newCondition;
}

void WeatherModel::setCurrentWindSpeed(const qint16 windspeed) {
    if (m_current.windSpeed != windspeed) m_current.windSpeed = windspeed;
}

void WeatherModel::setCurrentWindSpeedUnit(const qint8 unit) {
    if (unit < METERSPERSECOND || unit > MILESPERHOUR) return;

    auto newUnit = static_cast<WindSpeedUnit>(unit);
    if (m_current.windSpeedUnit != newUnit) m_current.windSpeedUnit = newUnit;
}

void WeatherModel::setDestinationProvinceName(const qint8 id) {
    if (id < ANGIANG || id > VINHLONG) return;

    auto newProvince = static_cast<Province>(id);
    if (m_destination.province != newProvince) m_destination.province = newProvince;
}

void WeatherModel::setDestinationTemperature(const qint16 temperature) {
    if (m_destination.temperature != temperature) m_destination.temperature = temperature;
}

void WeatherModel::setDestinationTemperatureUnit(const qint8 unit) {
    if (unit < DEGREE || unit > KELVIN) return;

    auto newUnit = static_cast<TemperatureUnit>(unit);
    if (m_destination.temperatureUnit != newUnit) m_destination.temperatureUnit = newUnit;
}

void WeatherModel::setDestinationCondition(const qint8 condition) {
    auto newCondition = static_cast<Condition>(condition);
    if (m_destination.condition != newCondition) m_destination.condition = newCondition;
}

void WeatherModel::setDestinationWindSpeed(const qint16 windspeed) {
    if (m_destination.windSpeed != windspeed) m_destination.windSpeed = windspeed;
}

void WeatherModel::setDestinationWindSpeedUnit(const qint8 unit) {
    if (unit < METERSPERSECOND || unit > MILESPERHOUR) return;

    auto newUnit = static_cast<WindSpeedUnit>(unit);
    if (m_destination.windSpeedUnit != newUnit) m_destination.windSpeedUnit = newUnit;
}

qint16 WeatherModel::convertCelsiusToFahrenheit(const qint16 celsius) {
    return static_cast<qint16>((celsius * 9.0f / 5.0f) + 32.0f + 0.5f);
}

qint16 WeatherModel::convertFahrenheitToCelsius(const qint16 fahrenheit) {
    return static_cast<qint16>((fahrenheit - 32.0f) * 5.0f / 9.0f + 0.5f);
}

qint16 WeatherModel::convertCelsiusToKelvin(const qint16 celsius) {
    return static_cast<qint16>(celsius + 273.15f + 0.5f);
}

qint16 WeatherModel::convertKelvinToCelsius(const qint16 kelvin) {
    return static_cast<qint16>(kelvin - 273.15f - 0.5f);
}

qint16 WeatherModel::convertMetersPerSecondToKilometersPerHour(const qint16 mps) {
    return static_cast<qint16>(mps * 3.6f + 0.5f);
}

qint16 WeatherModel::convertMetersPerSecondToMilesPerHour(const qint16 mps) {
    return static_cast<qint16>(mps * 2.23694f + 0.5f);
}
