#include "streamingmodel.h"

StreamingModel::StreamingModel(QObject *parent)
    : QObject(parent)
{
    m_video.inputPath = "";
    m_video.outputPath = "";

    m_video.videoWidth = 0;
    m_video.videoHeight = 0;
    m_video.videoRatio = 1.0f;
    m_video.isRatioConst = true;

    m_video.sourceWidth = 0;
    m_video.sourceHeight = 0;
    m_video.sourceRatio = 1.0f;
    m_video.sourceFPS = 0.0f;

    m_video.frameRate = 60;
    m_video.isStreaming = false;

    connect(&m_decoder, &FFmpegDecoder::onFrameDecoded, this,
    [this](const QImage &frame,
           qint16 videoWidth, qint16 videoHeight, float videoRatio,
           qint16 sourceWidth, qint16 sourceHeight, float sourceRatio,
           qint16 frameRate, qint16 sourceFPS)
    {
        setVideoWidth(videoWidth);
        setVideoHeight(videoHeight);
        setVideoRatio(videoRatio);

        setSourceWidth(sourceWidth);
        setSourceHeight(sourceHeight);
        setSourceRatio(sourceRatio);

        setFrameRate(frameRate);
        setSourceFPS(sourceFPS);

        emit onFrameReady(frame);
    });
}

QString StreamingModel::getInputPath() const
{
    return m_video.inputPath;
}

QString StreamingModel::getOutputPath() const
{
    return m_video.outputPath;
}

qint16 StreamingModel::getVideoWidth() const
{
    return m_video.videoWidth;
}

qint16 StreamingModel::getVideoHeight() const
{
    return m_video.videoHeight;
}

float StreamingModel::getVideoRatio() const
{
    return m_video.videoRatio;
}

bool StreamingModel::isRatioConst() const
{
    return m_video.isRatioConst;
}

qint16 StreamingModel::getSourceWidth() const
{
    return m_video.sourceWidth;
}

qint16 StreamingModel::getSourceHeight() const
{
    return m_video.sourceHeight;
}

float StreamingModel::getSourceRatio() const
{
    return m_video.sourceRatio;
}

float StreamingModel::getSourceFPS() const
{
    return m_video.sourceFPS;
}

qint16 StreamingModel::getFrameRate() const
{
    return m_video.frameRate;
}

bool StreamingModel::isStreaming() const
{
    return m_video.isStreaming;
}

void StreamingModel::setInputPath(const QString& path)
{
    m_video.inputPath = path;
    m_decoder.setInputPath(path);
}

void StreamingModel::setOutputPath(const QString& path)
{
    m_video.outputPath = path;
}

void StreamingModel::setVideoWidth(const qint16 width)
{
    m_video.videoWidth = width;
}

void StreamingModel::setVideoHeight(const qint16 height)
{
    m_video.videoHeight = height;
}

void StreamingModel::setVideoRatio(const float ratio)
{
    m_video.videoRatio = ratio;
}

void StreamingModel::setRatioConst(const bool ratioConst)
{
    m_video.isRatioConst = ratioConst;
}

void StreamingModel::setSourceWidth(const qint16 width)
{
    m_video.sourceWidth = width;
}

void StreamingModel::setSourceHeight(const qint16 height)
{
    m_video.sourceHeight = height;
}

void StreamingModel::setSourceRatio(const float ratio)
{
    m_video.sourceRatio = ratio;
}

void StreamingModel::setSourceFPS(const float fps)
{
    m_video.sourceFPS = fps;
}

void StreamingModel::setFrameRate(const qint16 frameRate)
{
    m_video.frameRate = frameRate;
}

void StreamingModel::setStreaming(const bool streaming)
{
    m_video.isStreaming = streaming;
}

void StreamingModel::startDecoding()
{
    if (m_video.inputPath.isEmpty()) return;

    m_decoder.startDecoding();
    m_video.isStreaming = true;
}

void StreamingModel::stopDecoding()
{
    m_decoder.stopDecoding();
    m_video.isStreaming = false;
}
