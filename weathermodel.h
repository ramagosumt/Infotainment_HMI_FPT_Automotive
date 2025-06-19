#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <QObject>

class WeatherModel : public QObject
{
    Q_OBJECT

public:
    enum Province {
        ANGIANG,
        BACNINH,
        CAMAU,
        CANTHO,
        CAOBANG,
        DAKLAK,
        DANANG,
        DIENBIEN,
        DONGNAI,
        DONGTHAP,
        GIALAI,
        HAIPHONG,
        HANOI,
        HATINH,
        HOCHIMINH,
        HUE,
        HUNGYEN,
        KHANHHOA,
        LAICHAU,
        LAMDONG,
        LANGSON,
        LAOCAI,
        NGHEAN,
        NINHBINH,
        PHUTHO,
        QUANGNGAI,
        QUANGNINH,
        QUANGTRI,
        SONLA,
        TAYNINH,
        THAINGUYEN,
        THANHHOA,
        TUYENQUANG,
        VINHLONG
    };
    Q_ENUM(Province)

    enum TemperatureUnit {
        DEGREE,
        FAHRENHEIT,
        KELVIN
    };
    Q_ENUM(TemperatureUnit)

    enum Condition {
        CLOUDY,
        FOGGY,
        PARTLYCLOUDY,
        RAINY,
        STORMY,
        SUNNY
    };
    Q_ENUM(Condition)

    enum WindSpeedUnit {
        METERSPERSECOND,
        KILOMETERSPERHOUR,
        MILESPERHOUR
    };
    Q_ENUM(WindSpeedUnit)

    struct WeatherData {
        Province            province;

        qint8               temperature;
        TemperatureUnit     temperatureUnit;

        Condition           condition;

        qint8               windSpeed;
        WindSpeedUnit       windSpeedUnit;
    };

    explicit WeatherModel(QObject *parent = nullptr);

    qint8 getCurrentProvinceName()          const;
    qint8 getCurrentTemperature()           const;
    qint8 getCurrentTemperatureUnit()       const;
    qint8 getCurrentCondition()             const;
    qint8 getCurrentWindSpeed()             const;
    qint8 getCurrentWindSpeedUnit()         const;

    qint8 getDestinationProvinceName()      const;
    qint8 getDestinationTemperature()       const;
    qint8 getDestinationTemperatureUnit()   const;
    qint8 getDestinationCondition()         const;
    qint8 getDestinationWindSpeed()         const;
    qint8 getDestinationWindSpeedUnit()     const;

    void setCurrentProvinceName(qint8 id);
    void setCurrentTemperature(qint8 temperature);
    void setCurrentTemperatureUnit(qint8 unit);
    void setCurrentCondition(qint8 condition);
    void setCurrentWindSpeed(qint8 windspeed);
    void setCurrentWindSpeedUnit(qint8 unit);

    void setDestinationProvinceName(qint8 id);
    void setDestinationTemperature(qint8 temperature);
    void setDestinationTemperatureUnit(qint8 unit);
    void setDestinationCondition(qint8 condition);
    void setDestinationWindSpeed(qint8 windspeed);
    void setDestinationWindSpeedUnit(qint8 unit);

    static qint8 convertCelsiusToFahrenheit(qint8 celsius);
    static qint8 convertFahrenheitToCelsius(qint8 fahrenheit);
    static qint8 convertCelsiusToKelvin(qint8 celsius);
    static qint8 convertKelvinToCelsius(qint8 kelvin);
    static qint8 convertMetersPerSecondToKilometersPerHour(qint8 mps);
    static qint8 convertMetersPerSecondToMilesPerHour(qint8 mps);

private:
    WeatherData m_current;
    WeatherData m_destination;
};

#endif // WEATHERMODEL_H
