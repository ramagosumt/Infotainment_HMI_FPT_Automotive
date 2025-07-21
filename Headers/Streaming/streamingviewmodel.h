#ifndef STREAMINGVIEWMODEL_H
#define STREAMINGVIEWMODEL_H

#include <QObject>
#include <QImage>

#include "streamingmodel.h"

class StreamingViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage  currentFrame                 READ getCurrentFrame                NOTIFY onCurrentFrameUpdated)
    Q_PROPERTY(QString inputPath                    READ getInputPath                   NOTIFY onInputPathChanged)
    Q_PROPERTY(QString outputPath                   READ getOutputPath                  NOTIFY onOutputPathChanged)
    Q_PROPERTY(qint16  videoWidth                   READ getVideoWidth                  NOTIFY onVideoWidthChanged)
    Q_PROPERTY(qint16  videoHeight                  READ getVideoHeight                 NOTIFY onVideoHeightChanged)
    Q_PROPERTY(float videoRatio                     READ getVideoRatio                  WRITE  setVideoRatio                        NOTIFY onVideoRatioChanged)
    Q_PROPERTY(bool    isRatioConst                 READ isRatioConst                   NOTIFY onRatioConstChanged)
    Q_PROPERTY(qint16  frameRate                    READ getFrameRate                   NOTIFY onFrameRateChanged)
    Q_PROPERTY(bool    isStreaming                  READ isStreaming                    NOTIFY onIsStreamingChanged)
    Q_PROPERTY(qint16  sourceWidth                  READ getSourceWidth                 NOTIFY onSourceWidthChanged)
    Q_PROPERTY(qint16  sourceHeight                 READ getSourceHeight                NOTIFY onSourceHeightChanged)
    Q_PROPERTY(float   sourceRatio                  READ getSourceRatio                 NOTIFY onSourceRatioChanged)
    Q_PROPERTY(qint16  sourceFPS                    READ getSourceFPS                   NOTIFY onSourceFPSChanged)

public:
    explicit StreamingViewModel(QObject *parent = nullptr);
    explicit StreamingViewModel(StreamingModel* model, QObject *parent = nullptr);
    ~StreamingViewModel();

    QImage getCurrentFrame()                                const;

    QString getInputPath()                                  const;
    QString getOutputPath()                                 const;
    qint16  getVideoWidth()                                 const;
    qint16  getVideoHeight()                                const;
    float   getVideoRatio()                                 const;
    bool    isRatioConst()                                  const;
    qint16  getFrameRate()                                  const;
    bool    isStreaming()                                   const;
    qint16  getSourceWidth()                                const;
    qint16  getSourceHeight()                               const;
    float   getSourceRatio()                                const;
    qint16  getSourceFPS()                                  const;

    Q_INVOKABLE void setOutputPath(const QString &path);
    Q_INVOKABLE void setVideoWidth(const qint16 width);
    Q_INVOKABLE void setVideoHeight(const qint16 height);
    Q_INVOKABLE void setVideoRatio(const float ratio);
    Q_INVOKABLE void setRatioConst(const bool ratioConst);
    Q_INVOKABLE void setFrameRate(const qint16 frameRate);
    Q_INVOKABLE void setIsStreaming(const bool streaming);
    Q_INVOKABLE void setSourceWidth(const qint16 width);
    Q_INVOKABLE void setSourceHeight(const qint16 height);
    Q_INVOKABLE void setSourceRatio(const float ratio);
    Q_INVOKABLE void setSourceFPS(const qint16 fps);

    Q_INVOKABLE void setInputPath(const QString &path);
    Q_INVOKABLE void startDecoding(qint16 width, qint16 height);
    Q_INVOKABLE void stopDecoding();

private:
    StreamingModel* streamingModel;
    QImage m_currentFrame;

    bool m_ownsModel = false;

    void setupConnections();
    void updateRatio();
    void updateFFmpeg();

signals:
    void onCurrentFrameUpdated();
    void onInputPathChanged();
    void onOutputPathChanged();
    void onVideoWidthChanged();
    void onVideoHeightChanged();
    void onVideoRatioChanged();
    void onRatioConstChanged();
    void onFrameRateChanged();
    void onIsStreamingChanged();
    void onSourceWidthChanged();
    void onSourceHeightChanged();
    void onSourceRatioChanged();
    void onSourceFPSChanged();
};

#endif // STREAMINGVIEWMODEL_H
