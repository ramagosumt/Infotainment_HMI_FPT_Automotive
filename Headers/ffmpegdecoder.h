#ifndef FFMPEGDECODER_H
#define FFMPEGDECODER_H

#include <QObject>
#include <QImage>
#include <QThread>
#include <QString>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

class FFmpegDecoder : public QObject
{
    Q_OBJECT

public:
    explicit FFmpegDecoder(QObject *parent = nullptr);
    ~FFmpegDecoder();

    void setInputPath(const QString &path);
    void startDecoding();
    void stopDecoding();

private:
    QString m_inputPath;
    QThread* m_workerThread;

    bool m_stopRequested;

    void decodingLoop();

signals:
    void onFrameDecoded(const QImage &frame, qint16 videoWidth, qint16 videoHeight, float videoRatio, qint16 sourceWidth, qint16 sourceHeight, float sourceRatio, qint16 frameRate, qint16 sourceFPS);
    void onDecodingFinished();
};

#endif // FFMPEGDECODER_H
