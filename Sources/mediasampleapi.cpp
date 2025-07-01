#include "mediasampleapi.h"

QList<MediaModel::MediaData> MediaSampleAPI::getSampleSongs()
{
    return {
        {MediaModel::UNSPECIFIED, "", "", "", 0, 0},
        {MediaModel::SPOTIFY, "m-tp M-TP", "Sơn Tùng M-TP", "Cơn Mưa Ngang Qua", 231000, 0},
        {MediaModel::SPOTIFY, "m-tp M-TP", "Sơn Tùng M-TP", "Nắng Ấm Xa Dần", 192000, 0},
        {MediaModel::SOUNDCLOUD, "m-tp M-TP", "Sơn Tùng M-TP", "Lạc Trôi", 273000, 0},
        {MediaModel::SOUNDCLOUD, "", "Sơn Tùng M-TP", "Chạy Ngay Đi", 274000, 0},
        {MediaModel::AMAZON, "", "Sơn Tùng M-TP", "Hãy Trao Cho Anh", 263000, 0},
        {MediaModel::AMAZON, "", "Sơn Tùng M-TP", "Muộn Rồi Mà Sao Còn", 289000, 0},
        {MediaModel::APPLE, "", "Sơn Tùng M-TP", "There’s No One At All", 222000, 0},
        {MediaModel::APPLE, "", "Sơn Tùng M-TP", "Making My Way", 258000, 0},
        {MediaModel::RADIO, "Chúng Ta", "Sơn Tùng M-TP", "Chúng Ta Của Tương Lai", 277000, 0},
        {MediaModel::USB, "", "Sơn Tùng M-TP", "Đừng Làm Trái Tim Anh Đau", 326000, 0},
        {MediaModel::USB, "", "AMee", "Em Bé", 326000, 0},
        {MediaModel::AMAZON, "", "Duongg", "3107", 227000, 0}
    };
}
