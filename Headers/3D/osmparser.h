#ifndef OSMPARSER_H
#define OSMPARSER_H

#include <QGeoCoordinate>
#include <QVector>
#include <QVector3D>
#include <QMap>

struct Building {
    QVector<QVector3D> footprint;
    float height;
};

struct Road {
    QVector<QVector3D> path;
    int laneCount;
};

class OSMParser
{
public:
    OSMParser();

    bool parse(const QString& filePath, const QGeoCoordinate& origin);

    const QVector<Building>& getBuildings() const;
    const QVector<Road>& getRoads() const;

private:
    QGeoCoordinate m_origin;
    QVector<Building> m_buildings;
    QVector<Road> m_roads;
    QMap<qint64, QGeoCoordinate> m_map;

    QVector3D convertGlobalToLocal(const QGeoCoordinate& global) const;
};

#endif // OSMPARSER_H
