#ifndef STREAMINGMODEL_H
#define STREAMINGMODEL_H

#include <QObject>
#include <QImage>

#include "ffmpegdecoder.h"

class StreamingModel : public QObject
{
    Q_OBJECT

public:
    struct StreamingData {
        QString             inputPath;
        QString             outputPath;

        qint16              videoWidth;
        qint16              videoHeight;
        float               videoRatio;
        bool                isRatioConst;

        qint16              frameRate;
        bool                isStreaming;

        qint16              sourceWidth;
        qint16              sourceHeight;
        float               sourceRatio;
        float               sourceFPS;
    };

    explicit StreamingModel(QObject *parent = nullptr);
    
    QString getInputPath()                  const;
    QString getOutputPath()                 const;

    qint16  getVideoWidth()                 const;
    qint16  getVideoHeight()                const;
    float   getVideoRatio()                 const;
    bool    isRatioConst()                  const;

    qint16  getSourceWidth()                const;
    qint16  getSourceHeight()               const;
    float   getSourceRatio()                const;
    float   getSourceFPS()                  const;

    qint16  getFrameRate()                  const;
    bool    isStreaming()                   const;

    void setInputPath(const QString& path);
    void setOutputPath(const QString& path);

    void setVideoWidth(const qint16 width);
    void setVideoHeight(const qint16 height);
    void setVideoRatio(const float ratio);
    void setRatioConst(const bool ratioConst);

    void setSourceWidth(const qint16 width);
    void setSourceHeight(const qint16 height);
    void setSourceRatio(const float ratio);
    void setSourceFPS(const float fps);

    void setFrameRate(const qint16 frameRate);
    void setStreaming(const bool streaming);
    
    void startDecoding(qint16 width, qint16 height);
    void stopDecoding();

    void updateFFmpeg();

private:
    StreamingData m_video;
    FFmpegDecoder m_decoder;

signals:
    void onFrameReady(const QImage &frame);
};

#endif // STREAMINGMODEL_H
