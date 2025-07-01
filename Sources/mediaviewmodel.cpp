#include "mediaviewmodel.h"
#include "mediasampleapi.h"

MediaViewModel::MediaViewModel(QObject *parent)
    : QObject(parent), mediaModel(new MediaModel(this)), m_ownsModel(true)
{}

MediaViewModel::MediaViewModel(MediaModel* model, QObject *parent)
    : QObject(parent), mediaModel(model)
{}

MediaViewModel::~MediaViewModel()
{
    if (m_ownsModel && mediaModel) delete mediaModel;
}

QStringList MediaViewModel::getSongDisplayList() const {
    QStringList list;
    const QList<MediaModel::MediaData>& songs = MediaSampleAPI::getSampleSongs();

    for (const auto& song : songs) list.append(song.song + " – " + song.artist);

    return list;
}

QVariantMap MediaViewModel::getSongObject(int index) const {
    QVariantMap map;
    const QList<MediaModel::MediaData>& songs = MediaSampleAPI::getSampleSongs();

    if (index < 0 || index >= songs.size()) return map;

    const MediaModel::MediaData& data = songs[index];

    map["source"] = static_cast<qint8>(data.source);
    map["album"] = data.album;
    map["artist"] = data.artist;
    map["song"] = data.song;
    map["duration"] = data.duration;
    map["time"] = data.time;

    return map;
}

QString MediaViewModel::getCurrentSource() const {
    return convertSourceToString(mediaModel->getCurrentMedia().source);
}

QString MediaViewModel::getCurrentAlbum() const {
    return mediaModel->getCurrentMedia().album;
}

QString MediaViewModel::getCurrentArtist() const {
    return mediaModel->getCurrentMedia().artist;
}

QString MediaViewModel::getCurrentSong() const {
    return mediaModel->getCurrentMedia().song;
}

QString MediaViewModel::getCurrentDuration() const {
    return convertDurationToString(mediaModel->getCurrentMedia().duration);
}

QString MediaViewModel::getCurrentTime() const {
    return convertDurationToString(mediaModel->getCurrentMedia().time);
}

QString MediaViewModel::getCurrentSourceIcon() const {
    return getSourceIconPath(mediaModel->getCurrentMedia().source);
}

QString MediaViewModel::getNextSource() const {
    return convertSourceToString(mediaModel->getNextMedia().source);
}

QString MediaViewModel::getNextAlbum() const {
    return mediaModel->getNextMedia().album;
}

QString MediaViewModel::getNextArtist() const {
    return mediaModel->getNextMedia().artist;
}

QString MediaViewModel::getNextSong() const {
    return mediaModel->getNextMedia().song;
}

QString MediaViewModel::getNextDuration() const {
    return convertDurationToString(mediaModel->getNextMedia().duration);
}

QString MediaViewModel::getNextTime() const {
    return convertDurationToString(mediaModel->getNextMedia().time);
}

QString MediaViewModel::getNextSourceIcon() const {
    return getSourceIconPath(mediaModel->getNextMedia().source);
}

qint8 MediaViewModel::getCurrentSourceRaw() const {
    return static_cast<qint8>(mediaModel->getCurrentMedia().source);
}

qint32 MediaViewModel::getCurrentDurationRaw() const {
    return mediaModel->getCurrentMedia().duration;
}

qint32 MediaViewModel::getCurrentTimeRaw() const {
    return mediaModel->getCurrentMedia().time;
}

qint8 MediaViewModel::getNextSourceRaw() const {
    return static_cast<qint8>(mediaModel->getNextMedia().source);
}

qint32 MediaViewModel::getNextDurationRaw() const {
    return mediaModel->getNextMedia().duration;
}

qint32 MediaViewModel::getNextTimeRaw() const {
    return mediaModel->getNextMedia().time;
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

    mediaModel->setCurrentMedia(data);
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

    mediaModel->setNextMedia(data);
    emit onNextMediaChanged();
}

void MediaViewModel::setCurrentTime(qint32 time) {
    if (time == mediaModel->getCurrentMedia().time) return;

    MediaModel::MediaData data = mediaModel->getCurrentMedia();
    data.time = time;
    mediaModel->setCurrentMedia(data);
    emit onCurrentMediaChanged();
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
        return "qrc:/WeatherApp_MVVM/assets/images/media/AmazonMusic100.png";
    case MediaModel::APPLE:
        return "qrc:/WeatherApp_MVVM/assets/images/media/AppleMusic100.png";
    case MediaModel::RADIO:
        return "qrc:/WeatherApp_MVVM/assets/images/media/Radio100.png";
    case MediaModel::SOUNDCLOUD:
        return "qrc:/WeatherApp_MVVM/assets/images/media/SoundCloud100.png";
    case MediaModel::SPOTIFY:
        return "qrc:/WeatherApp_MVVM/assets/images/media/Spotify100.png";
    case MediaModel::USB:
        return "qrc:/WeatherApp_MVVM/assets/images/media/USB100.png";
    case MediaModel::UNSPECIFIED:
    default:
        return "";
    }
}
