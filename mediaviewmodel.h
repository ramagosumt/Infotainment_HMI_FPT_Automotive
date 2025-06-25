#ifndef MEDIAVIEWMODEL_H
#define MEDIAVIEWMODEL_H

#include <QObject>

#include "mediamodel.h"

class MediaViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList songDisplayList      READ getSongDisplayList         CONSTANT)

    Q_PROPERTY(QString currentSource            READ getCurrentSource           NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString currentAlbum             READ getCurrentAlbum            NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString currentArtist            READ getCurrentArtist           NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString currentSong              READ getCurrentSong             NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString currentDuration          READ getCurrentDuration         NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString currentTime              READ getCurrentTime             NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(qint32  currentTimeRaw           READ getCurrentTimeRaw          NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString currentSourceIcon        READ getCurrentSourceIcon       NOTIFY onCurrentMediaChanged)

    Q_PROPERTY(QString nextSource               READ getNextSource              NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString nextAlbum                READ getNextAlbum               NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString nextArtist               READ getNextArtist              NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString nextSong                 READ getNextSong                NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString nextDuration             READ getNextDuration            NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString nextTime                 READ getNextTime                NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(qint32  nextTimeRaw              READ getNextTimeRaw             NOTIFY onCurrentMediaChanged)
    Q_PROPERTY(QString nextSourceIcon           READ getNextSourceIcon          NOTIFY onCurrentMediaChanged)

public:
    explicit MediaViewModel(QObject *parent = nullptr);

    QStringList getSongDisplayList() const;

    Q_INVOKABLE QVariantMap getSongObject(int index) const;

    Q_INVOKABLE QString getCurrentSource()      const;
    Q_INVOKABLE QString getCurrentAlbum()       const;
    Q_INVOKABLE QString getCurrentArtist()      const;
    Q_INVOKABLE QString getCurrentSong()        const;
    Q_INVOKABLE QString getCurrentDuration()    const;
    Q_INVOKABLE QString getCurrentTime()        const;
    Q_INVOKABLE QString getCurrentSourceIcon()  const;

    Q_INVOKABLE QString getNextSource()         const;
    Q_INVOKABLE QString getNextAlbum()          const;
    Q_INVOKABLE QString getNextArtist()         const;
    Q_INVOKABLE QString getNextSong()           const;
    Q_INVOKABLE QString getNextDuration()       const;
    Q_INVOKABLE QString getNextTime()           const;
    Q_INVOKABLE QString getNextSourceIcon()     const;

    Q_INVOKABLE qint8   getCurrentSourceRaw()   const;
    Q_INVOKABLE qint32  getCurrentDurationRaw() const;
    Q_INVOKABLE qint32  getCurrentTimeRaw()     const;

    Q_INVOKABLE qint8   getNextSourceRaw()      const;
    Q_INVOKABLE qint32  getNextDurationRaw()    const;
    Q_INVOKABLE qint32  getNextTimeRaw()        const;

    Q_INVOKABLE void setCurrentMedia(const qint8 source, const QString &album, const QString &artist,
                                     const QString &song, const qint32 duration, const qint32 time);

    Q_INVOKABLE void setCurrentTime(const qint32 time);

    Q_INVOKABLE void setNextMedia(const qint8 source, const QString &album, const QString &artist,
                                     const QString &song, const qint32 duration, const qint32 time);

private:
    MediaModel mediaModel;

    QString convertSourceToString(qint8 source) const;
    QString convertDurationToString(qint32 duration) const;
    QString getSourceIconPath(qint8 source) const;

signals:
    void onCurrentMediaChanged();
    void onNextMediaChanged();
};

#endif // MEDIAVIEWMODEL_H
