#ifndef STREAMINGMODEL_H
#define STREAMINGMODEL_H

#include <QObject>

class StreamingModel : public QObject
{
    Q_OBJECT

public:
    struct StreamingData {
        QString             inputPath;      // Source file, device, etc.
        QString             outputPath;     // Encoded output target (likely stream URL)

        qint16              videoWidth;
        qint16              videoHeight;

        float               videoRatio;     // Aspect ratio (e.g., 1.0 for 1:1, 2.0 for 16:8)
        bool                isRatioConst;   // Maintain constant aspect ratio if true

        qint16              frameRate;      // Target FPS (within your 40-60 range ideally)

        bool                isStreaming;    // True when streaming is active
    };

    explicit StreamingModel(QObject *parent = nullptr);

    QString getInputPath()                  const;
    QString getOutputPath()                 const;
    qint16  getVideoWidth()                 const;
    qint16  getVideoHeight()                const;
    float   getVideoRatio()                 const;
    bool    isRatioConst()                  const;
    qint16  getFrameRate()                  const;
    bool    isStreaming()                   const;

    void setInputPath(const QString& path);
    void setOutputPath(const QString& path);
    void setVideoWidth(const qint16 width);
    void setVideoHeight(const qint16 height);
    void setVideoRatio(const float ratio);
    void setRatioConst(const bool ratioConst);
    void setFrameRate(const qint16 frameRate);
    void setStreaming(const bool streaming);

private:
    StreamingData m_video;
};

#endif // STREAMINGMODEL_H
