#ifndef MEDIAMODEL_H
#define MEDIAMODEL_H

#include <QObject>
#include <QString>

class MediaModel : public QObject
{
    Q_OBJECT

public:
    enum Source {
        AMAZON,
        APPLE,
        RADIO,
        SOUNDCLOUD,
        SPOTIFY,
        USB,
        UNSPECIFIED
    };
    Q_ENUM(Source)

    struct MediaData {
        Source              source;

        QString             album;
        QString             artist;
        QString             song;

        qint32              duration;
        qint32              time;
    };

    explicit MediaModel(QObject *parent = nullptr);

    MediaData getCurrentMedia()             const;
    MediaData getNextMedia()                const;

    void setCurrentMedia(const MediaData &data);
    void setNextMedia(const MediaData &data);

private:
    MediaData m_current;
    MediaData m_next;
};

#endif // MEDIAMODEL_H
