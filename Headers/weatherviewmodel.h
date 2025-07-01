#ifndef WEATHERVIEWMODEL_H
#define WEATHERVIEWMODEL_H

#include <QObject>

#include "weathermodel.h"

class WeatherViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentProvinceName          READ getCurrentProvinceName         NOTIFY onCurrentProvinceNameChanged)
    Q_PROPERTY(QString currentTemperature           READ getCurrentTemperature          NOTIFY onCurrentTemperatureChanged)
    Q_PROPERTY(QString currentTemperatureUnit       READ getCurrentTemperatureUnit      NOTIFY onCurrentTemperatureUnitChanged)
    Q_PROPERTY(QString currentCondition             READ getCurrentCondition            NOTIFY onCurrentConditionChanged)
    Q_PROPERTY(QString currentWindSpeed             READ getCurrentWindSpeed            NOTIFY onCurrentWindSpeedChanged)
    Q_PROPERTY(QString currentWindSpeedUnit         READ getCurrentWindSpeedUnit        NOTIFY onCurrentWindSpeedUnitChanged)

    Q_PROPERTY(QString destinationProvinceName      READ getDestinationProvinceName     NOTIFY onDestinationProvinceNameChanged)
    Q_PROPERTY(QString destinationTemperature       READ getDestinationTemperature      NOTIFY onDestinationTemperatureChanged)
    Q_PROPERTY(QString destinationTemperatureUnit   READ getDestinationTemperatureUnit  NOTIFY onDestinationTemperatureUnitChanged)
    Q_PROPERTY(QString destinationCondition         READ getDestinationCondition        NOTIFY onDestinationConditionChanged)
    Q_PROPERTY(QString destinationWindSpeed         READ getDestinationWindSpeed        NOTIFY onDestinationWindSpeedChanged)
    Q_PROPERTY(QString destinationWindSpeedUnit     READ getDestinationWindSpeedUnit    NOTIFY onDestinationWindSpeedUnitChanged)

    Q_PROPERTY(QString currentConditionIcon         READ getCurrentConditionIcon        NOTIFY onCurrentConditionIconChanged)
    Q_PROPERTY(QString destinationConditionIcon     READ getDestinationConditionIcon    NOTIFY onDestinationConditionIconChanged)

public:
    explicit WeatherViewModel(QObject *parent = nullptr);
    explicit WeatherViewModel(WeatherModel* model, QObject *parent = nullptr);

    ~WeatherViewModel();

    Q_INVOKABLE QString getCurrentProvinceName()            const;
    Q_INVOKABLE QString getCurrentTemperature()             const;
    Q_INVOKABLE QString getCurrentTemperatureUnit()         const;
    Q_INVOKABLE QString getCurrentCondition()               const;
    Q_INVOKABLE QString getCurrentWindSpeed()               const;
    Q_INVOKABLE QString getCurrentWindSpeedUnit()           const;

    Q_INVOKABLE QString getDestinationProvinceName()        const;
    Q_INVOKABLE QString getDestinationTemperature()         const;
    Q_INVOKABLE QString getDestinationTemperatureUnit()     const;
    Q_INVOKABLE QString getDestinationCondition()           const;
    Q_INVOKABLE QString getDestinationWindSpeed()           const;
    Q_INVOKABLE QString getDestinationWindSpeedUnit()       const;

    Q_INVOKABLE qint8 getCurrentProvinceRaw()               const;
    Q_INVOKABLE qint8 getCurrentTemperatureRaw()            const;
    Q_INVOKABLE qint8 getCurrentTemperatureUnitRaw()        const;
    Q_INVOKABLE qint8 getCurrentConditionRaw()              const;
    Q_INVOKABLE qint8 getCurrentWindSpeedRaw()              const;
    Q_INVOKABLE qint8 getCurrentWindSpeedUnitRaw()          const;

    Q_INVOKABLE qint8 getDestinationProvinceRaw()           const;
    Q_INVOKABLE qint8 getDestinationTemperatureRaw()        const;
    Q_INVOKABLE qint8 getDestinationTemperatureUnitRaw()    const;
    Q_INVOKABLE qint8 getDestinationConditionRaw()          const;
    Q_INVOKABLE qint8 getDestinationWindSpeedRaw()          const;
    Q_INVOKABLE qint8 getDestinationWindSpeedUnitRaw()      const;

    Q_INVOKABLE QString getCurrentConditionIcon()           const;
    Q_INVOKABLE QString getDestinationConditionIcon()       const;

    Q_INVOKABLE void setCurrentProvinceName(const qint8 id);
    Q_INVOKABLE void setCurrentTemperature(const qint8 temperature);
    Q_INVOKABLE void setCurrentTemperatureUnit(const qint8 unit);
    Q_INVOKABLE void setCurrentCondition(const qint8 condition);
    Q_INVOKABLE void setCurrentWindSpeed(const qint8 windspeed);
    Q_INVOKABLE void setCurrentWindSpeedUnit(const qint8 unit);

    Q_INVOKABLE void setDestinationProvinceName(const qint8 id);
    Q_INVOKABLE void setDestinationTemperature(const qint8 temperature);
    Q_INVOKABLE void setDestinationTemperatureUnit(const qint8 unit);
    Q_INVOKABLE void setDestinationCondition(const qint8 condition);
    Q_INVOKABLE void setDestinationWindSpeed(const qint8 windspeed);
    Q_INVOKABLE void setDestinationWindSpeedUnit(const qint8 unit);

private:
    WeatherModel* weatherModel;

    bool m_ownsModel = false;

    QString convertProvinceToString(qint8 id)               const;
    QString convertTemperatureUnitToString(qint8 unit)      const;
    QString convertConditionToString(qint8 condition)       const;
    QString convertWindSpeedUnitToString(qint8 unit)        const;

signals:
    void onCurrentProvinceNameChanged();
    void onCurrentTemperatureChanged();
    void onCurrentTemperatureUnitChanged();
    void onCurrentConditionChanged();
    void onCurrentWindSpeedChanged();
    void onCurrentWindSpeedUnitChanged();

    void onDestinationProvinceNameChanged();
    void onDestinationTemperatureChanged();
    void onDestinationTemperatureUnitChanged();
    void onDestinationConditionChanged();
    void onDestinationWindSpeedChanged();
    void onDestinationWindSpeedUnitChanged();

    void onCurrentConditionIconChanged();
    void onDestinationConditionIconChanged();
};

#endif // WEATHERVIEWMODEL_H
