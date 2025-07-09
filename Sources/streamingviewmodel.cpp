#include "streamingviewmodel.h"

StreamingViewModel::StreamingViewModel(QObject *parent)
    : QObject(parent), streamingModel(new StreamingModel(this)), m_ownsModel(true)
{
    setupConnections();
}

StreamingViewModel::StreamingViewModel(StreamingModel* model, QObject *parent)
    : QObject(parent), streamingModel(model), m_ownsModel(false)
{
    setupConnections();
}

StreamingViewModel::~StreamingViewModel()
{
    if (m_ownsModel && streamingModel) delete streamingModel;
}

QImage StreamingViewModel::getCurrentFrame() const
{
    return m_currentFrame;
}

QString StreamingViewModel::getInputPath() const
{
    return streamingModel->getInputPath();
}

QString StreamingViewModel::getOutputPath() const
{
    return streamingModel->getOutputPath();
}

qint16 StreamingViewModel::getVideoWidth() const
{
    return streamingModel->getVideoWidth();
}

qint16 StreamingViewModel::getVideoHeight() const
{
    return streamingModel->getVideoHeight();
}

float StreamingViewModel::getVideoRatio() const
{
    return streamingModel->getVideoRatio();
}

bool StreamingViewModel::isRatioConst() const
{
    return streamingModel->isRatioConst();
}

qint16 StreamingViewModel::getFrameRate() const
{
    return streamingModel->getFrameRate();
}

bool StreamingViewModel::isStreaming() const
{
    return streamingModel->isStreaming();
}

qint16 StreamingViewModel::getSourceWidth() const {
    return streamingModel->getSourceWidth();
}

qint16 StreamingViewModel::getSourceHeight() const {
    return streamingModel->getSourceHeight();
}

float StreamingViewModel::getSourceRatio() const {
    return streamingModel->getSourceRatio();
}

qint16 StreamingViewModel::getSourceFPS() const {
    return streamingModel->getSourceFPS();
}

void StreamingViewModel::setInputPath(const QString &path)
{
    if (path == streamingModel->getInputPath()) return;
    streamingModel->setInputPath(path);
    emit onInputPathChanged();
}

void StreamingViewModel::setOutputPath(const QString &path)
{
    if (path == streamingModel->getOutputPath()) return;
    streamingModel->setOutputPath(path);
    emit onOutputPathChanged();
}

void StreamingViewModel::setVideoWidth(qint16 width)
{
    if (width == streamingModel->getVideoWidth()) return;
    streamingModel->setVideoWidth(width);
    emit onVideoWidthChanged();
}

void StreamingViewModel::setVideoHeight(qint16 height)
{
    if (height == streamingModel->getVideoHeight()) return;
    streamingModel->setVideoHeight(height);
    emit onVideoHeightChanged();
}

void StreamingViewModel::setVideoRatio(float ratio)
{
    if (ratio == streamingModel->getVideoRatio()) return;
    streamingModel->setVideoRatio(ratio);
    emit onVideoRatioChanged();

    updateRatio();
    streamingModel->updateFFmpeg();
}

void StreamingViewModel::setRatioConst(bool ratioConst)
{
    if (ratioConst == streamingModel->isRatioConst()) return;
    streamingModel->setRatioConst(ratioConst);
    emit onRatioConstChanged();
}

void StreamingViewModel::setFrameRate(qint16 frameRate)
{
    if (frameRate == streamingModel->getFrameRate()) return;
    streamingModel->setFrameRate(frameRate);
    emit onFrameRateChanged();
}

void StreamingViewModel::setIsStreaming(bool streaming)
{
    if (streaming == streamingModel->isStreaming()) return;
    streamingModel->setStreaming(streaming);
    emit onIsStreamingChanged();
}

void StreamingViewModel::setSourceWidth(qint16 width) {
    if (width == streamingModel->getSourceWidth()) return;
    streamingModel->setSourceWidth(width);
    emit onSourceWidthChanged();
}

void StreamingViewModel::setSourceHeight(qint16 height) {
    if (height == streamingModel->getSourceHeight()) return;
    streamingModel->setSourceHeight(height);
    emit onSourceHeightChanged();
}

void StreamingViewModel::setSourceRatio(float ratio) {
    if (ratio == streamingModel->getSourceRatio()) return;
    streamingModel->setSourceRatio(ratio);
    emit onSourceRatioChanged();
}

void StreamingViewModel::setSourceFPS(qint16 fps) {
    if (fps == streamingModel->getSourceFPS()) return;
    streamingModel->setSourceFPS(fps);
    emit onSourceFPSChanged();
}

void StreamingViewModel::startDecoding(qint16 width, qint16 height)
{
    streamingModel->startDecoding(width, height);
    emit onIsStreamingChanged();
}

void StreamingViewModel::stopDecoding()
{
    streamingModel->stopDecoding();
    emit onIsStreamingChanged();
}

void StreamingViewModel::setupConnections()
{
    connect(streamingModel, &StreamingModel::onFrameReady, this, [this](const QImage &frame) {
        m_currentFrame = frame;
        emit onCurrentFrameUpdated();

        emit onInputPathChanged();
        emit onOutputPathChanged();
        emit onVideoWidthChanged();
        emit onVideoHeightChanged();
        emit onVideoRatioChanged();
        emit onRatioConstChanged();
        emit onFrameRateChanged();
        emit onIsStreamingChanged();
        emit onSourceWidthChanged();
        emit onSourceHeightChanged();
        emit onSourceRatioChanged();
        emit onSourceFPSChanged();
    });
}

void StreamingViewModel::updateRatio() {
    const int baseWidth = 240;

    qint16 videoWidth = baseWidth;
    qint16 videoHeight = static_cast<qint16>(baseWidth / getVideoRatio());

    setVideoWidth(videoWidth);
    setVideoHeight(videoHeight);
}
