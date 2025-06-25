#ifndef MEDIAMODEL_H
#define MEDIAMODEL_H

#include <QObject>
#include <QVariantMap>

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

    inline static const int count = 13;

    inline static const MediaData songs[count] = {
        {UNSPECIFIED, "", "", "", 0, 0},
        {SPOTIFY, "m-tp M-TP", "Sơn Tùng M-TP", "Cơn Mưa Ngang Qua", 231000, 0},
        {SPOTIFY, "m-tp M-TP", "Sơn Tùng M-TP", "Nắng Ấm Xa Dần", 192000, 0},
        {SOUNDCLOUD, "m-tp M-TP", "Sơn Tùng M-TP", "Lạc Trôi", 273000, 0},
        {SOUNDCLOUD, "", "Sơn Tùng M-TP", "Chạy Ngay Đi", 274000, 0},
        {AMAZON, "", "Sơn Tùng M-TP", "Hãy Trao Cho Anh", 263000, 0},
        {AMAZON, "", "Sơn Tùng M-TP", "Muộn Rồi Mà Sao Còn", 289000, 0},
        {APPLE, "", "Sơn Tùng M-TP", "There’s No One At All", 222000, 0},
        {APPLE, "", "Sơn Tùng M-TP", "Making My Way", 258000, 0},
        {RADIO, "Chúng Ta", "Sơn Tùng M-TP", "Chúng Ta Của Tương Lai", 277000, 0},
        {USB, "", "Sơn Tùng M-TP", "Đừng Làm Trái Tim Anh Đau", 326000, 0},
        {USB, "", "AMee", "Em Bé", 326000, 0},
        {AMAZON, "", "Duongg", "3107", 326000, 0}
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
