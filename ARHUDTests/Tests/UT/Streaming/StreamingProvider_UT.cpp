#include <gtest/gtest.h>
#include "Streaming/streamingprovider.h"

class StreamingProviderTest : public ::testing::Test {
protected:
    StreamingProvider provider;
};

// 1. Default frame is null
TEST_F(StreamingProviderTest, DefaultFrameIsNull) {
    QSize outSize;
    QImage result = provider.requestImage("ignored", &outSize, QSize(100, 100));
    EXPECT_TRUE(result.isNull());
}

// 2. Can set and retrieve a frame
TEST_F(StreamingProviderTest, SetAndGetFrame) {
    QImage frame(640, 480, QImage::Format_RGB32);
    frame.fill(Qt::red);
    provider.setFrame(frame);

    QSize outSize;
    QImage result = provider.requestImage("ignored", &outSize, QSize(0, 0));

    EXPECT_EQ(result.size(), frame.size());
    EXPECT_FALSE(result.isNull());
}

// 3. Requested size with no frame should not crash
TEST_F(StreamingProviderTest, NullFrameWithRequestedSize) {
    QSize outSize;
    QImage img = provider.requestImage("ignored", &outSize, QSize(128, 128));
    EXPECT_TRUE(img.isNull());
}

// 4. Returned outSize matches actual frame size
TEST_F(StreamingProviderTest, OutSizeMatchesFrame) {
    QImage frame(320, 200, QImage::Format_RGB32);
    provider.setFrame(frame);

    QSize outSize;
    QImage result = provider.requestImage("ignored", &outSize, QSize());
    EXPECT_EQ(outSize, frame.size());
}

// 5. Multiple setFrame calls do not crash
TEST_F(StreamingProviderTest, MultipleSetFrameSafe) {
    QImage f1(100, 100, QImage::Format_RGB32);
    QImage f2(200, 150, QImage::Format_RGB32);

    provider.setFrame(f1);
    provider.setFrame(f2);

    QSize outSize;
    QImage result = provider.requestImage("ignored", &outSize, QSize());
    EXPECT_EQ(result.size(), f2.size());
}

// 6. requestImage is safe to call repeatedly
TEST_F(StreamingProviderTest, MultipleRequestImageSafe) {
    QImage frame(50, 50, QImage::Format_RGB32);
    provider.setFrame(frame);

    for (int i = 0; i < 5; ++i) {
        QSize outSize;
        QImage result = provider.requestImage("frame", &outSize, QSize());
        EXPECT_FALSE(result.isNull());
    }
}

// 7. Frame remains unchanged if set repeatedly to same data
TEST_F(StreamingProviderTest, RepeatedSameFrameIdempotent) {
    QImage frame(60, 60, QImage::Format_RGB32);
    provider.setFrame(frame);
    provider.setFrame(frame);

    QSize outSize;
    QImage result = provider.requestImage("any", &outSize, QSize());
    EXPECT_EQ(result.size(), QSize(60, 60));
}

// 8. Request image with empty id returns last frame
TEST_F(StreamingProviderTest, RequestImageEmptyIdStillWorks) {
    QImage frame(70, 70, QImage::Format_RGB32);
    provider.setFrame(frame);

    QSize outSize;
    QImage result = provider.requestImage("", &outSize, QSize());
    EXPECT_EQ(result.size(), frame.size());
}
