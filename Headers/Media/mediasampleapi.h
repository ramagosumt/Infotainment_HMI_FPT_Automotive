#ifndef MEDIASAMPLEAPI_H
#define MEDIASAMPLEAPI_H

#include <QObject>
#include <QList>

#include "mediamodel.h"

class MediaSampleAPI : public QObject
{
    Q_OBJECT

public:
    static QList<MediaModel::MediaData> getSampleSongs();
};

#endif // MEDIASAMPLEAPI_H
