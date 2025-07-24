#include <gtest/gtest.h>
#include "Weather/weatherviewmodel.h"

class WeatherViewModelTest : public ::testing::Test {
protected:
    WeatherModel model;
    WeatherViewModel viewModel{&model};
};

// 1. Get current province name as string
TEST_F(WeatherViewModelTest, GetCurrentProvinceName) {
    model.setCurrentProvinceName(WeatherModel::HANOI);
    EXPECT_EQ(viewModel.getCurrentProvinceName(), "Ha Noi");
}

// 2. Get current temperature as string
TEST_F(WeatherViewModelTest, GetCurrentTemperature) {
    model.setCurrentTemperature(21);
    EXPECT_EQ(viewModel.getCurrentTemperature(), "21");
}

// 3. Get current temperature unit as string
TEST_F(WeatherViewModelTest, GetCurrentTemperatureUnit) {
    model.setCurrentTemperatureUnit(WeatherModel::KELVIN);
    EXPECT_EQ(viewModel.getCurrentTemperatureUnit(), "K");
}

// 4. Get current condition as string
TEST_F(WeatherViewModelTest, GetCurrentCondition) {
    model.setCurrentCondition(WeatherModel::CLOUDY);
    EXPECT_EQ(viewModel.getCurrentCondition(), "Cloudy");
}

// 5. Get current wind speed as string
TEST_F(WeatherViewModelTest, GetCurrentWindSpeed) {
    model.setCurrentWindSpeed(18);
    EXPECT_EQ(viewModel.getCurrentWindSpeed(), "18");
}

// 6. Get current wind speed unit as string
TEST_F(WeatherViewModelTest, GetCurrentWindSpeedUnit) {
    model.setCurrentWindSpeedUnit(WeatherModel::KILOMETERSPERHOUR);
    EXPECT_EQ(viewModel.getCurrentWindSpeedUnit(), "km/h");
}

// 7. Get destination province name as string
TEST_F(WeatherViewModelTest, GetDestinationProvinceName) {
    model.setDestinationProvinceName(WeatherModel::HUE);
    EXPECT_EQ(viewModel.getDestinationProvinceName(), "Hue");
}

// 8. Get destination temperature as string
TEST_F(WeatherViewModelTest, GetDestinationTemperature) {
    model.setDestinationTemperature(33);
    EXPECT_EQ(viewModel.getDestinationTemperature(), "33");
}

// 9. Get destination temperature unit as string
TEST_F(WeatherViewModelTest, GetDestinationTemperatureUnit) {
    model.setDestinationTemperatureUnit(WeatherModel::FAHRENHEIT);
    EXPECT_EQ(viewModel.getDestinationTemperatureUnit(), "°F");
}

// 10. Get destination condition as string
TEST_F(WeatherViewModelTest, GetDestinationCondition) {
    model.setDestinationCondition(WeatherModel::FOGGY);
    EXPECT_EQ(viewModel.getDestinationCondition(), "Foggy");
}

// 11. Get destination wind speed as string
TEST_F(WeatherViewModelTest, GetDestinationWindSpeed) {
    model.setDestinationWindSpeed(24);
    EXPECT_EQ(viewModel.getDestinationWindSpeed(), "24");
}

// 12. Get destination wind speed unit as string
TEST_F(WeatherViewModelTest, GetDestinationWindSpeedUnit) {
    model.setDestinationWindSpeedUnit(WeatherModel::MILESPERHOUR);
    EXPECT_EQ(viewModel.getDestinationWindSpeedUnit(), "mph");
}

// 13–18: Raw getters for current weather
TEST_F(WeatherViewModelTest, GetCurrentRawValues) {
    model.setCurrentProvinceName(WeatherModel::HOCHIMINH);
    model.setCurrentTemperature(25);
    model.setCurrentTemperatureUnit(WeatherModel::FAHRENHEIT);
    model.setCurrentCondition(WeatherModel::RAINY);
    model.setCurrentWindSpeed(11);
    model.setCurrentWindSpeedUnit(WeatherModel::MILESPERHOUR);

    EXPECT_EQ(viewModel.getCurrentProvinceRaw(), WeatherModel::HOCHIMINH);
    EXPECT_EQ(viewModel.getCurrentTemperatureRaw(), 25);
    EXPECT_EQ(viewModel.getCurrentTemperatureUnitRaw(), WeatherModel::FAHRENHEIT);
    EXPECT_EQ(viewModel.getCurrentConditionRaw(), WeatherModel::RAINY);
    EXPECT_EQ(viewModel.getCurrentWindSpeedRaw(), 11);
    EXPECT_EQ(viewModel.getCurrentWindSpeedUnitRaw(), WeatherModel::MILESPERHOUR);
}

// 19–24: Raw getters for destination weather
TEST_F(WeatherViewModelTest, GetDestinationRawValues) {
    model.setDestinationProvinceName(WeatherModel::HATINH);
    model.setDestinationTemperature(29);
    model.setDestinationTemperatureUnit(WeatherModel::DEGREE);
    model.setDestinationCondition(WeatherModel::CLOUDY);
    model.setDestinationWindSpeed(3);
    model.setDestinationWindSpeedUnit(WeatherModel::METERSPERSECOND);

    EXPECT_EQ(viewModel.getDestinationProvinceRaw(), WeatherModel::HATINH);
    EXPECT_EQ(viewModel.getDestinationTemperatureRaw(), 29);
    EXPECT_EQ(viewModel.getDestinationTemperatureUnitRaw(), WeatherModel::DEGREE);
    EXPECT_EQ(viewModel.getDestinationConditionRaw(), WeatherModel::CLOUDY);
    EXPECT_EQ(viewModel.getDestinationWindSpeedRaw(), 3);
    EXPECT_EQ(viewModel.getDestinationWindSpeedUnitRaw(), WeatherModel::METERSPERSECOND);
}

// 25. Get current condition icon name
TEST_F(WeatherViewModelTest, GetCurrentConditionIcon) {
    model.setCurrentCondition(WeatherModel::SUNNY);
    EXPECT_TRUE(viewModel.getCurrentConditionIcon().endsWith("Sunny100.png"));
}

// 26. Get destination condition icon name
TEST_F(WeatherViewModelTest, GetDestinationConditionIcon) {
    model.setDestinationCondition(WeatherModel::STORMY);
    EXPECT_TRUE(viewModel.getDestinationConditionIcon().endsWith("Stormy100.png"));
}

// 27. Set current province and reflect in model
TEST_F(WeatherViewModelTest, SetCurrentProvinceThroughViewModel) {
    viewModel.setCurrentProvinceName(WeatherModel::DANANG);
    EXPECT_EQ(model.getCurrentProvinceName(), WeatherModel::DANANG);
}

// 28. Set current temperature and reflect in model
TEST_F(WeatherViewModelTest, SetCurrentTemperatureThroughViewModel) {
    viewModel.setCurrentTemperature(15);
    EXPECT_EQ(model.getCurrentTemperature(), 15);
}

// 29. Set destination condition and reflect in model
TEST_F(WeatherViewModelTest, SetDestinationConditionThroughViewModel) {
    viewModel.setDestinationCondition(WeatherModel::PARTLYCLOUDY);
    EXPECT_EQ(model.getDestinationCondition(), WeatherModel::PARTLYCLOUDY);
}

// 30. Set destination wind speed and reflect in model
TEST_F(WeatherViewModelTest, SetDestinationWindSpeedThroughViewModel) {
    viewModel.setDestinationWindSpeed(7);
    EXPECT_EQ(model.getDestinationWindSpeed(), 7);
}
