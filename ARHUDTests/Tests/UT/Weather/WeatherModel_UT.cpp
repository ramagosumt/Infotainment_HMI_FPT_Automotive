#include <gtest/gtest.h>
#include "Weather/weathermodel.h"

class WeatherModelTest : public ::testing::Test {
protected:
    WeatherModel model;
};

// 1. Default province is valid
TEST_F(WeatherModelTest, DefaultCurrentProvinceIsValid) {
    EXPECT_GE(model.getCurrentProvinceName(), 0);
    EXPECT_LE(model.getCurrentProvinceName(), WeatherModel::VINHLONG);
}

// 2. Can set and get current temperature
TEST_F(WeatherModelTest, SetGetCurrentTemperature) {
    model.setCurrentTemperature(30);
    EXPECT_EQ(model.getCurrentTemperature(), 30);
}

// 3. Can set and get current temperature unit
TEST_F(WeatherModelTest, SetGetCurrentTemperatureUnit) {
    model.setCurrentTemperatureUnit(WeatherModel::FAHRENHEIT);
    EXPECT_EQ(model.getCurrentTemperatureUnit(), WeatherModel::FAHRENHEIT);
}

// 4. Can set and get current condition
TEST_F(WeatherModelTest, SetGetCurrentCondition) {
    model.setCurrentCondition(WeatherModel::STORMY);
    EXPECT_EQ(model.getCurrentCondition(), WeatherModel::STORMY);
}

// 5. Can set and get current wind speed
TEST_F(WeatherModelTest, SetGetCurrentWindSpeed) {
    model.setCurrentWindSpeed(15);
    EXPECT_EQ(model.getCurrentWindSpeed(), 15);
}

// 6. Can set and get current wind speed unit
TEST_F(WeatherModelTest, SetGetCurrentWindSpeedUnit) {
    model.setCurrentWindSpeedUnit(WeatherModel::KILOMETERSPERHOUR);
    EXPECT_EQ(model.getCurrentWindSpeedUnit(), WeatherModel::KILOMETERSPERHOUR);
}

// 7. Can set and get destination province
TEST_F(WeatherModelTest, SetGetDestinationProvince) {
    model.setDestinationProvinceName(WeatherModel::HUE);
    EXPECT_EQ(model.getDestinationProvinceName(), WeatherModel::HUE);
}

// 8. Can set and get destination temperature
TEST_F(WeatherModelTest, SetGetDestinationTemperature) {
    model.setDestinationTemperature(22);
    EXPECT_EQ(model.getDestinationTemperature(), 22);
}

// 9. Can set and get destination temperature unit
TEST_F(WeatherModelTest, SetGetDestinationTemperatureUnit) {
    model.setDestinationTemperatureUnit(WeatherModel::KELVIN);
    EXPECT_EQ(model.getDestinationTemperatureUnit(), WeatherModel::KELVIN);
}

// 10. Can set and get destination condition
TEST_F(WeatherModelTest, SetGetDestinationCondition) {
    model.setDestinationCondition(WeatherModel::FOGGY);
    EXPECT_EQ(model.getDestinationCondition(), WeatherModel::FOGGY);
}

// 11. Can set and get destination wind speed
TEST_F(WeatherModelTest, SetGetDestinationWindSpeed) {
    model.setDestinationWindSpeed(8);
    EXPECT_EQ(model.getDestinationWindSpeed(), 8);
}

// 12. Can set and get destination wind speed unit
TEST_F(WeatherModelTest, SetGetDestinationWindSpeedUnit) {
    model.setDestinationWindSpeedUnit(WeatherModel::MILESPERHOUR);
    EXPECT_EQ(model.getDestinationWindSpeedUnit(), WeatherModel::MILESPERHOUR);
}

// 13. Conversion Celsius to Fahrenheit
TEST_F(WeatherModelTest, ConvertCelsiusToFahrenheit) {
    EXPECT_EQ(WeatherModel::convertCelsiusToFahrenheit(0), 32);
    EXPECT_EQ(WeatherModel::convertCelsiusToFahrenheit(100), 212);
}

// 14. Conversion Fahrenheit to Celsius
TEST_F(WeatherModelTest, ConvertFahrenheitToCelsius) {
    EXPECT_EQ(WeatherModel::convertFahrenheitToCelsius(32), 0);
    EXPECT_EQ(WeatherModel::convertFahrenheitToCelsius(212), 100);
}

// 15. Conversion Kelvin to Celsius
TEST_F(WeatherModelTest, ConvertKelvinToCelsius) {
    EXPECT_EQ(WeatherModel::convertKelvinToCelsius(273), 0);
    EXPECT_EQ(WeatherModel::convertKelvinToCelsius(373), 99);
}

// 16. Round-trip Celsius → Fahrenheit → Celsius
TEST_F(WeatherModelTest, RoundTripCelsiusFahrenheit) {
    qint16 original = 25;
    auto fahrenheit = WeatherModel::convertCelsiusToFahrenheit(original);
    auto celsius = WeatherModel::convertFahrenheitToCelsius(fahrenheit);
    EXPECT_NEAR(celsius, original, 1);  // Because of flooring/rounding
}

// 17. Round-trip Celsius → Kelvin → Celsius
TEST_F(WeatherModelTest, RoundTripCelsiusKelvin) {
    qint16 original = 30;
    auto kelvin = WeatherModel::convertCelsiusToKelvin(original);
    auto celsius = WeatherModel::convertKelvinToCelsius(kelvin);
    EXPECT_NEAR(celsius, original, 1);
}

// 18. Negative Celsius to Fahrenheit
TEST_F(WeatherModelTest, NegativeCelsiusToFahrenheit) {
    EXPECT_EQ(WeatherModel::convertCelsiusToFahrenheit(-40), -40);
}

// 19. Zero windspeed conversion to km/h
TEST_F(WeatherModelTest, ZeroWindSpeedToKmH) {
    EXPECT_EQ(WeatherModel::convertMetersPerSecondToKilometersPerHour(0), 0);
}

// 20. Zero windspeed conversion to mph
TEST_F(WeatherModelTest, ZeroWindSpeedToMph) {
    EXPECT_EQ(WeatherModel::convertMetersPerSecondToMilesPerHour(0), 0);
}

// 21. Set all current weather values and verify coherence
TEST_F(WeatherModelTest, FullSetCurrentWeather) {
    model.setCurrentProvinceName(WeatherModel::HANOI);
    model.setCurrentTemperature(20);
    model.setCurrentTemperatureUnit(WeatherModel::DEGREE);
    model.setCurrentCondition(WeatherModel::RAINY);
    model.setCurrentWindSpeed(5);
    model.setCurrentWindSpeedUnit(WeatherModel::METERSPERSECOND);

    EXPECT_EQ(model.getCurrentProvinceName(), WeatherModel::HANOI);
    EXPECT_EQ(model.getCurrentTemperature(), 20);
    EXPECT_EQ(model.getCurrentTemperatureUnit(), WeatherModel::DEGREE);
    EXPECT_EQ(model.getCurrentCondition(), WeatherModel::RAINY);
    EXPECT_EQ(model.getCurrentWindSpeed(), 5);
    EXPECT_EQ(model.getCurrentWindSpeedUnit(), WeatherModel::METERSPERSECOND);
}

// 22. Set all destination weather values and verify coherence
TEST_F(WeatherModelTest, FullSetDestinationWeather) {
    model.setDestinationProvinceName(WeatherModel::DANANG);
    model.setDestinationTemperature(35);
    model.setDestinationTemperatureUnit(WeatherModel::FAHRENHEIT);
    model.setDestinationCondition(WeatherModel::SUNNY);
    model.setDestinationWindSpeed(10);
    model.setDestinationWindSpeedUnit(WeatherModel::KILOMETERSPERHOUR);

    EXPECT_EQ(model.getDestinationProvinceName(), WeatherModel::DANANG);
    EXPECT_EQ(model.getDestinationTemperature(), 35);
    EXPECT_EQ(model.getDestinationTemperatureUnit(), WeatherModel::FAHRENHEIT);
    EXPECT_EQ(model.getDestinationCondition(), WeatherModel::SUNNY);
    EXPECT_EQ(model.getDestinationWindSpeed(), 10);
    EXPECT_EQ(model.getDestinationWindSpeedUnit(), WeatherModel::KILOMETERSPERHOUR);
}

// 23. Convert 1 m/s to km/h (should be 4)
TEST_F(WeatherModelTest, Convert1MpsToKmH) {
    EXPECT_EQ(WeatherModel::convertMetersPerSecondToKilometersPerHour(1), 4);
}

// 24. Convert 1 m/s to mph (should be ~2)
TEST_F(WeatherModelTest, Convert1MpsToMph) {
    EXPECT_EQ(WeatherModel::convertMetersPerSecondToMilesPerHour(1), 2);
}

// 25. Edge: set extreme temperature
TEST_F(WeatherModelTest, SetExtremeTemperature) {
    model.setCurrentTemperature(-273);  // Absolute zero
    EXPECT_EQ(model.getCurrentTemperature(), -273);
}

// 26. Invalid enum values are retained (no validation in header)
TEST_F(WeatherModelTest, InvalidTemperatureUnitSet) {
    model.setCurrentTemperatureUnit(WeatherModel::DEGREE);
    model.setCurrentTemperatureUnit(99);  // Undefined
    EXPECT_EQ(model.getCurrentTemperatureUnit(), WeatherModel::DEGREE); // Should remain unchanged
}

// 27. Set both current and destination and ensure no cross-contamination
TEST_F(WeatherModelTest, CurrentAndDestinationAreIndependent) {
    model.setCurrentTemperature(10);
    model.setDestinationTemperature(50);

    EXPECT_EQ(model.getCurrentTemperature(), 10);
    EXPECT_EQ(model.getDestinationTemperature(), 50);
}

// 28. Switching wind unit doesn't alter value automatically
TEST_F(WeatherModelTest, WindUnitSwitchDoesNotConvert) {
    model.setCurrentWindSpeed(10);
    model.setCurrentWindSpeedUnit(WeatherModel::METERSPERSECOND);
    model.setCurrentWindSpeedUnit(WeatherModel::MILESPERHOUR);

    // Value should remain unchanged
    EXPECT_EQ(model.getCurrentWindSpeed(), 10);
    EXPECT_EQ(model.getCurrentWindSpeedUnit(), WeatherModel::MILESPERHOUR);
}

// 29. Province enums are usable as integers
TEST_F(WeatherModelTest, ProvinceEnumCastsCorrectly) {
    EXPECT_EQ(static_cast<int>(WeatherModel::HOCHIMINH), 14);
}

// 30. All enums defined in range
TEST_F(WeatherModelTest, AllEnumValuesInRange) {
    EXPECT_LT(WeatherModel::SUNNY, 6);
    EXPECT_LT(WeatherModel::KELVIN, 3);
    EXPECT_LT(WeatherModel::VINHLONG, 35);
}

