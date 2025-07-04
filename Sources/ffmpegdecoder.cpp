#include "ffmpegdecoder.h"
#include <QDateTime>
#include <QDebug>

FFmpegDecoder::FFmpegDecoder(QObject *parent)
    : QObject(parent), m_workerThread(nullptr)
{}

FFmpegDecoder::~FFmpegDecoder()
{
    stopDecoding();
}

void FFmpegDecoder::setInputPath(const QString &path)
{
    m_inputPath = path;
}

void FFmpegDecoder::startDecoding()
{
    if (m_workerThread && m_workerThread->isRunning()) return;

    m_stopRequested = false;

    m_workerThread = QThread::create([this] { decodingLoop(); });

    connect(m_workerThread, &QThread::finished, m_workerThread, &QObject::deleteLater);

    m_workerThread->start();
}

void FFmpegDecoder::stopDecoding()
{
    m_stopRequested = true;

    if (m_workerThread && m_workerThread->isRunning()) {
        m_workerThread->quit();
        m_workerThread->wait();
    }

    m_workerThread = nullptr;
}

void FFmpegDecoder::decodingLoop()
{
    AVFormatContext* formatCtx = nullptr;
    if (avformat_open_input(&formatCtx, m_inputPath.toStdString().c_str(), nullptr, nullptr) != 0) return;
    if (avformat_find_stream_info(formatCtx, nullptr) < 0) { avformat_close_input(&formatCtx); return; }

    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatCtx->nb_streams; ++i) {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }
    if (videoStreamIndex == -1) { avformat_close_input(&formatCtx); return; }

    AVCodecParameters* codecParams = formatCtx->streams[videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecParams->codec_id);
    if (!codec) { avformat_close_input(&formatCtx); return; }

    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecCtx, codecParams);
    avcodec_open2(codecCtx, codec, nullptr);

    AVRational timeBase = formatCtx->streams[videoStreamIndex]->time_base;

    double sourceFPS = av_q2d(formatCtx->streams[videoStreamIndex]->avg_frame_rate);
    if (sourceFPS <= 0.0) sourceFPS = 60.0;

    const int smoothingWindow = 60;
    QList<qint64> frameTimes;

    AVPacket* packet = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();
    SwsContext* swsCtx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
                                        codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,
                                        SWS_BILINEAR, nullptr, nullptr, nullptr);

    uint8_t* rgbData[4];
    int rgbLinesize[4];
    av_image_alloc(rgbData, rgbLinesize, codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24, 1);

    qint64 lastPtsMs = -1;
    QElapsedTimer frameTimer;
    frameTimer.start();

    while (!m_stopRequested) {

        while (!m_stopRequested && av_read_frame(formatCtx, packet) >= 0) {

            if (packet->stream_index == videoStreamIndex) {
                if (avcodec_send_packet(codecCtx, packet) == 0) {
                    while (avcodec_receive_frame(codecCtx, frame) == 0) {

                        int64_t pts = frame->pts;
                        qint64 ptsMs = -1;
                        if (pts != AV_NOPTS_VALUE)
                            ptsMs = static_cast<qint64>(pts * av_q2d(timeBase) * 1000.0);

                        qint64 now = QDateTime::currentMSecsSinceEpoch();
                        frameTimes.append(now);
                        if (frameTimes.size() > smoothingWindow) frameTimes.removeFirst();

                        float videoFPS = 0;
                        if (frameTimes.size() >= 2) {
                            qint64 totalTime = frameTimes.last() - frameTimes.first();
                            if (totalTime > 0)
                                videoFPS = 1000.0 * (frameTimes.size() - 1) / totalTime;
                        }

                        if (lastPtsMs >= 0 && ptsMs > 0) {
                            qint64 expectedDelay = ptsMs - lastPtsMs;
                            qint64 elapsed = frameTimer.elapsed();

                            if (elapsed < expectedDelay)
                                QThread::msleep(expectedDelay - elapsed);

                            frameTimer.restart();
                        }
                        lastPtsMs = ptsMs;

                        sws_scale(swsCtx, frame->data, frame->linesize, 0, codecCtx->height, rgbData, rgbLinesize);
                        QImage img(rgbData[0], codecCtx->width, codecCtx->height, rgbLinesize[0], QImage::Format_RGB888);

                        int cropWidth = 720, cropHeight = 405, detectedX = 860, detectedY = 390;
                        int cropX = qBound(0, detectedX - cropWidth / 2, img.width() - cropWidth);
                        int cropY = qBound(0, detectedY - cropHeight / 2, img.height() - cropHeight);

                        QImage cropped = img.copy(cropX, cropY, cropWidth, cropHeight);

                        emit onFrameDecoded(cropped, cropWidth, cropHeight,
                                            static_cast<float>(cropWidth) / cropHeight,
                                            codecCtx->width, codecCtx->height,
                                            static_cast<float>(codecCtx->width) / codecCtx->height,
                                            static_cast<qint16>(videoFPS), static_cast<qint16>(sourceFPS));
                    }
                }
            }

            av_packet_unref(packet);
        }

        if (m_stopRequested)
            break;

        avcodec_flush_buffers(codecCtx);
        if (av_seek_frame(formatCtx, videoStreamIndex, 0, AVSEEK_FLAG_BACKWARD) < 0)
            break;

        lastPtsMs = -1;
        frameTimer.restart();
    }

    av_freep(&rgbData[0]);
    sws_freeContext(swsCtx);
    av_frame_free(&frame);
    av_packet_free(&packet);
    avcodec_free_context(&codecCtx);
    avformat_close_input(&formatCtx);

    emit onDecodingFinished();
}
