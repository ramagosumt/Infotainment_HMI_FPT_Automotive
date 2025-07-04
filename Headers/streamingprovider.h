#ifndef STREAMINGPROVIDER_H
#define STREAMINGPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>
#include <QMutex>

class StreamingProvider : public QQuickImageProvider
{
public:
    StreamingProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    void setFrame(const QImage &frame);

private:
    QImage m_frame;
    QMutex m_mutex;
};

#endif // STREAMINGPROVIDER_H
