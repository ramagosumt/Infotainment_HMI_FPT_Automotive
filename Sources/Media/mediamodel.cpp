#include "Media/mediamodel.h"
#include "Media/mediasampleapi.h"

MediaModel::MediaModel(QObject *parent)
    : QObject(parent)
{
    const QList<MediaData>& songs = MediaSampleAPI::getSampleSongs();

    if (songs.size() > 12)
        m_current = songs[12];
    else
        m_current = { UNSPECIFIED, "", "", "", 0, 0 };

    m_next = { UNSPECIFIED, "", "", "", 0, 0 };
}

MediaModel::MediaData MediaModel::getCurrentMedia() const {
    return m_current;
}

MediaModel::MediaData MediaModel::getNextMedia() const {
    return m_next;
}

void MediaModel::setCurrentMedia(const MediaData &data) {
    m_current = data;
}

void MediaModel::setNextMedia(const MediaData &data) {
    m_next = data;
}
