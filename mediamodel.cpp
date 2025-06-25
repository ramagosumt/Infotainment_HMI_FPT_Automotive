#include "mediamodel.h"

MediaModel::MediaModel(QObject *parent)
    : QObject{parent}
{
    m_current = songs[12];

    m_next.source = UNSPECIFIED;
    m_next.album = "";
    m_next.artist = "";
    m_next.song = "";
    m_next.duration = 0;
    m_next.time = 0;
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
