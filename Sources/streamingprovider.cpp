#include "streamingprovider.h"

StreamingProvider::StreamingProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage StreamingProvider::requestImage(const QString &, QSize *size, const QSize &)
{
    QMutexLocker locker(&m_mutex);
    if (size)
        *size = m_frame.size();

    return m_frame;
}

void StreamingProvider::setFrame(const QImage &frame)
{
    QMutexLocker locker(&m_mutex);
    m_frame = frame;
}
