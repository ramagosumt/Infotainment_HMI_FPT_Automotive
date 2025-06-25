#include "mediaviewmodel.h"

MediaViewModel::MediaViewModel(QObject *parent)
    : QObject{parent}
{}

QStringList MediaViewModel::getSongDisplayList() const {
    QStringList list;
    for (int i = 0; i < MediaModel::count; ++i) list.append(MediaModel::songs[i].song + " – " + MediaModel::songs[i].artist);

    return list;
}

QVariantMap MediaViewModel::getSongObject(int index) const {
    QVariantMap map;
    if (index < 0 || index >= MediaModel::count) return map;

    map["source"] = MediaModel::songs[index].source;
    map["album"] = MediaModel::songs[index].album;
    map["artist"] = MediaModel::songs[index].artist;
    map["song"] = MediaModel::songs[index].song;
    map["duration"] = MediaModel::songs[index].duration;
    map["time"] = MediaModel::songs[index].time;

    return map;
}

QString MediaViewModel::getCurrentSource() const {
    return convertSourceToString(mediaModel.getCurrentMedia().source);
}

QString MediaViewModel::getCurrentAlbum() const {
    return mediaModel.getCurrentMedia().album;
}

QString MediaViewModel::getCurrentArtist() const {
    return mediaModel.getCurrentMedia().artist;
}

QString MediaViewModel::getCurrentSong() const {
    return mediaModel.getCurrentMedia().song;
}

QString MediaViewModel::getCurrentDuration() const {
    return convertDurationToString(mediaModel.getCurrentMedia().duration);
}

QString MediaViewModel::getCurrentTime() const {
    return convertDurationToString(mediaModel.getCurrentMedia().time);
}

QString MediaViewModel::getCurrentSourceIcon() const {
    return getSourceIconPath(mediaModel.getCurrentMedia().source);
}

QString MediaViewModel::getNextSource() const {
    return convertSourceToString(mediaModel.getNextMedia().source);
}

QString MediaViewModel::getNextAlbum() const {
    return mediaModel.getNextMedia().album;
}

QString MediaViewModel::getNextArtist() const {
    return mediaModel.getNextMedia().artist;
}

QString MediaViewModel::getNextSong() const {
    return mediaModel.getNextMedia().song;
}

QString MediaViewModel::getNextDuration() const {
    return convertDurationToString(mediaModel.getNextMedia().duration);
}

QString MediaViewModel::getNextTime() const {
    return convertDurationToString(mediaModel.getNextMedia().time);
}

QString MediaViewModel::getNextSourceIcon() const {
    return getSourceIconPath(mediaModel.getNextMedia().source);
}

qint8 MediaViewModel::getCurrentSourceRaw() const {
    return static_cast<qint8>(mediaModel.getCurrentMedia().source);
}

qint32 MediaViewModel::getCurrentDurationRaw() const {
    return mediaModel.getCurrentMedia().duration;
}

qint32 MediaViewModel::getCurrentTimeRaw() const {
    return mediaModel.getCurrentMedia().time;
}

qint8 MediaViewModel::getNextSourceRaw() const {
    return static_cast<qint8>(mediaModel.getNextMedia().source);
}

qint32 MediaViewModel::getNextDurationRaw() const {
    return mediaModel.getNextMedia().duration;
}

qint32 MediaViewModel::getNextTimeRaw() const {
    return mediaModel.getNextMedia().time;
}

void MediaViewModel::setCurrentMedia(const qint8 source, const QString &album, const QString &artist,
                                     const QString &song, const qint32 duration, const qint32 time)
{
    MediaModel::MediaData data;
    data.source = static_cast<MediaModel::Source>(source);
    data.album = album;
    data.artist = artist;
    data.song = song;
    data.duration = duration;
    data.time = time;

    mediaModel.setCurrentMedia(data);
    emit onCurrentMediaChanged();
}

void MediaViewModel::setCurrentTime(qint32 time) {
    if (time == mediaModel.getCurrentMedia().time) return;

    MediaModel::MediaData data = mediaModel.getCurrentMedia();
    data.time = time;
    mediaModel.setCurrentMedia(data);
    emit onCurrentMediaChanged();
}

void MediaViewModel::setNextMedia(const qint8 source, const QString &album, const QString &artist,
                                  const QString &song, const qint32 duration, const qint32 time)
{
    MediaModel::MediaData data;
    data.source = static_cast<MediaModel::Source>(source);
    data.album = album;
    data.artist = artist;
    data.song = song;
    data.duration = duration;
    data.time = time;

    mediaModel.setNextMedia(data);
    emit onNextMediaChanged();
}

QString MediaViewModel::convertSourceToString(const qint8 source) const {
    switch (source) {
    case MediaModel::AMAZON:
        return "Amazon Music";
    case MediaModel::APPLE:
        return "Apple Music";
    case MediaModel::RADIO:
        return "Radio";
    case MediaModel::SOUNDCLOUD:
        return "SoundCloud";
    case MediaModel::SPOTIFY:
        return "Spotify";
    case MediaModel::USB:
        return "USB";
    case MediaModel::UNSPECIFIED:
        return "Out of Range";
    default:
        return "Out of Range";
    }
}

QString MediaViewModel::convertDurationToString(const qint32 duration) const {
    int totalSeconds = duration / 1000;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

QString MediaViewModel::getSourceIconPath(qint8 source) const {
    switch (source) {
    case MediaModel::AMAZON:
        return "assets/images/media/AmazonMusic100.png";
    case MediaModel::APPLE:
        return "assets/images/media/AppleMusic100.png";
    case MediaModel::RADIO:
        return "assets/images/media/Radio100.png";
    case MediaModel::SOUNDCLOUD:
        return "assets/images/media/SoundCloud100.png";
    case MediaModel::SPOTIFY:
        return "assets/images/media/Spotify100.png";
    case MediaModel::USB:
        return "assets/images/media/USB100.png";
    case MediaModel::UNSPECIFIED:
    default:
        return "";
    }
}
