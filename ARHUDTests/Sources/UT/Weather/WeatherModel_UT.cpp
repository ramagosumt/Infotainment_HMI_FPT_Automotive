#include <gtest/gtest.h>
#include "Weather/weathermodel.h"

TEST(WeatherModelTest, DefaultInitialization) {
    WeatherModel model;

    EXPECT_EQ(model.getCurrentProvinceName(), WeatherModel::HANOI);
    EXPECT_EQ(model.getCurrentTemperature(), 20);
    EXPECT_EQ(model.getCurrentTemperatureUnit(), WeatherModel::DEGREE);
    EXPECT_EQ(model.getCurrentCondition(), WeatherModel::SUNNY);
    EXPECT_EQ(model.getCurrentWindSpeed(), 5);
    EXPECT_EQ(model.getCurrentWindSpeedUnit(), WeatherModel::METERSPERSECOND);

    EXPECT_EQ(model.getDestinationProvinceName(), WeatherModel::THANHHOA);
    EXPECT_EQ(model.getDestinationTemperature(), 25);
    EXPECT_EQ(model.getDestinationCondition(), WeatherModel::RAINY);
    EXPECT_EQ(model.getDestinationWindSpeed(), 1);
}

TEST(WeatherModelTest, TemperatureConversion) {
    EXPECT_EQ(WeatherModel::convertCelsiusToFahrenheit(0), 32);
    EXPECT_EQ(WeatherModel::convertFahrenheitToCelsius(32), 0);
    EXPECT_EQ(WeatherModel::convertCelsiusToKelvin(0), 273);
    EXPECT_EQ(WeatherModel::convertKelvinToCelsius(273), 0);
}

TEST(WeatherModelTest, WindSpeedConversion) {
    EXPECT_EQ(WeatherModel::convertMetersPerSecondToKilometersPerHour(1), 4);
    EXPECT_EQ(WeatherModel::convertMetersPerSecondToMilesPerHour(1), 2);
}

TEST(WeatherModelTest, SetterValidation) {
    WeatherModel model;

    model.setCurrentTemperature(30);
    EXPECT_EQ(model.getCurrentTemperature(), 30);

    model.setCurrentProvinceName(static_cast<qint8>(WeatherModel::CAMAU));
    EXPECT_EQ(model.getCurrentProvinceName(), WeatherModel::CAMAU);

    model.setDestinationCondition(static_cast<qint8>(WeatherModel::STORMY));
    EXPECT_EQ(model.getDestinationCondition(), WeatherModel::STORMY);
}

TEST(WeatherModelTest, InvalidEnumRangeIgnored) {
    WeatherModel model;

    model.setCurrentProvinceName(-1);
    EXPECT_NE(model.getCurrentProvinceName(), -1);  // Should remain unchanged

    model.setCurrentTemperatureUnit(99);  // Invalid
    EXPECT_NE(model.getCurrentTemperatureUnit(), 99);
}
