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
    m_video.frameRate = 60;
    m_video.isStreaming = false;
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

void StreamingModel::setFrameRate(const qint16 frameRate)
{
    m_video.frameRate = frameRate;
}

void StreamingModel::setStreaming(const bool streaming)
{
    m_video.isStreaming = streaming;
}
