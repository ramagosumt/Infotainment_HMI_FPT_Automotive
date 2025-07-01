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

        qint16              temperature;
        TemperatureUnit     temperatureUnit;

        Condition           condition;

        qint16              windSpeed;
        WindSpeedUnit       windSpeedUnit;
    };

    explicit WeatherModel(QObject *parent = nullptr);

    qint8  getCurrentProvinceName()         const;
    qint16 getCurrentTemperature()          const;
    qint8  getCurrentTemperatureUnit()      const;
    qint8  getCurrentCondition()            const;
    qint16 getCurrentWindSpeed()            const;
    qint8  getCurrentWindSpeedUnit()        const;

    qint8  getDestinationProvinceName()     const;
    qint16 getDestinationTemperature()      const;
    qint8  getDestinationTemperatureUnit()  const;
    qint8  getDestinationCondition()        const;
    qint16 getDestinationWindSpeed()        const;
    qint8  getDestinationWindSpeedUnit()    const;

    void setCurrentProvinceName(const qint8 id);
    void setCurrentTemperature(const qint16 temperature);
    void setCurrentTemperatureUnit(const qint8 unit);
    void setCurrentCondition(const qint8 condition);
    void setCurrentWindSpeed(const qint16 windspeed);
    void setCurrentWindSpeedUnit(const qint8 unit);

    void setDestinationProvinceName(const qint8 id);
    void setDestinationTemperature(const qint16 temperature);
    void setDestinationTemperatureUnit(const qint8 unit);
    void setDestinationCondition(const qint8 condition);
    void setDestinationWindSpeed(const qint16 windspeed);
    void setDestinationWindSpeedUnit(const qint8 unit);

    static qint16 convertCelsiusToFahrenheit(const qint16 celsius);
    static qint16 convertFahrenheitToCelsius(const qint16 fahrenheit);
    static qint16 convertCelsiusToKelvin(const qint16 celsius);
    static qint16 convertKelvinToCelsius(const qint16 kelvin);
    static qint16 convertMetersPerSecondToKilometersPerHour(const qint16 mps);
    static qint16 convertMetersPerSecondToMilesPerHour(const qint16 mps);

private:
    WeatherData m_current;
    WeatherData m_destination;
};

#endif // WEATHERMODEL_H
