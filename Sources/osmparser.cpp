#include "osmparser.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>

OSMParser::OSMParser() {

}

bool OSMParser::parse(const QString &filePath, const QGeoCoordinate &origin) {
    // Set the origin coordinate for local ENU conversion
    m_origin = origin;

    // Clear any previously parsed data
    m_buildings.clear();
    m_roads.clear();
    m_map.clear();

    // Open the specified OSM XML file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;

    // Create an XML reader for parsing
    QXmlStreamReader xml(&file);

    // Temporary variables for parsing a single <way> block
    QVector<qint64> currentNodes;
    QMap<QString, QString> currentTags;
    qint64 currentId = -1;
    bool isBuilding = false;
    bool isRoad = false;

    // Main XML parsing loop
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            const QStringView name = xml.name();

            // <node> represents a point with lat/lon and ID
            if (name == QLatin1String("node")) {
                qint64 id = xml.attributes().value("id").toLongLong();
                double lat = xml.attributes().value("lat").toDouble();
                double lon = xml.attributes().value("lon").toDouble();

                m_map[id] = QGeoCoordinate(lat, lon); // Save it to the node map

                // <way> starts a new building or road
            } else if (name == QLatin1String("way")) {
                currentNodes.clear();
                currentTags.clear();

                isBuilding = isRoad = false;

                currentId = xml.attributes().value("id").toLongLong();

                // <nd> refers to a node by ID, used within a <way>
            } else if (name == QLatin1String("nd")) {
                qint64 ref = xml.attributes().value("ref").toLongLong();

                currentNodes.append(ref);

                // <tag> contains metadata like "building", "lanes", etc.
            } else if (name == QLatin1String("tag")) {
                QString k = xml.attributes().value("k").toString();
                QString v = xml.attributes().value("v").toString();

                currentTags[k] = v;

                // Mark flags for building or road based on tags
                if (k == "building" && v != "no") isBuilding = true;
                if (k == "highway") isRoad = true;
            }

            // Finished reading a <way>, process it as building or road
        } else if (xml.isEndElement() && xml.name() == "way") {
            if (isBuilding) {
                Building b;
                for (qint64 id : currentNodes) {
                    if (m_map.contains(id))
                        b.footprint.append(convertGlobalToLocal(m_map[id]));
                }

                // Default height = 10.0 if not specified
                b.height = currentTags.contains("height") ? currentTags["height"].toFloat() : 10.0f;
                m_buildings.append(b);
            }

            if (isRoad) {
                Road r;
                for (qint64 id : currentNodes) {
                    if (m_map.contains(id))
                        r.path.append(convertGlobalToLocal(m_map[id]));
                }

                // Default lane count = 2 if not specified
                r.laneCount = currentTags.contains("lanes") ? currentTags["lanes"].toInt() : 2;
                m_roads.append(r);
            }
        }
    }

    // Return true if parsing finished successfully (no XML errors)
    return !xml.hasError();
}

const QVector<Building>& OSMParser::getBuildings() const {
    return m_buildings;
}

const QVector<Road>& OSMParser::getRoads() const {
    return m_roads;
}

QVector3D OSMParser::convertGlobalToLocal(const QGeoCoordinate& global) const {
    // Calculate the straight-line distance (in meters) between the origin and the global coordinate
    double d = m_origin.distanceTo(global);

    // Calculate the azimuth between the origin and the global coordinate, then convert it to radians for use in trigonometric functions
    double az = qDegreesToRadians(m_origin.azimuthTo(global));

    // Convert polar coordinates to local Cartesian coordinates (X, Y, Z): X = East, Y = Up, Z = North
    return {
        static_cast<float>(d * qSin(az)), // X: East direction
        0.0f,                             // Y: Up direction
        static_cast<float>(d * qCos(az))  // Z: North direction
    };
}
