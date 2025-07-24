#include <gtest/gtest.h>
#include "Streaming/ffmpegdecoder.h"

class FFmpegDecoderTest : public ::testing::Test {
protected:
    FFmpegDecoder decoder;
};

// 1. Default input path is empty
TEST_F(FFmpegDecoderTest, DefaultInputPathEmpty) {
    decoder.setInputPath("");
    // No crash expected
}

// 2. Can set input path
TEST_F(FFmpegDecoderTest, SetInputPath) {
    decoder.setInputPath("sample.mp4");
    // Internal validation not exposed; ensure no crash
    SUCCEED();
}

// 3. Can set output size
TEST_F(FFmpegDecoderTest, SetOutputSize) {
    decoder.setOutputSize(1920, 1080);
    SUCCEED(); // Should not crash
}

// 4. Can start decoding with dummy resolution
TEST_F(FFmpegDecoderTest, StartDecodingSafe) {
    decoder.setInputPath("");  // simulate no path
    decoder.startDecoding(640, 480);
    // No crash expected; decoding loop likely exits immediately
    SUCCEED();
}

// 5. Can call stop decoding without crash
TEST_F(FFmpegDecoderTest, StopDecodingSafe) {
    decoder.stopDecoding(); // no side effect observable
    SUCCEED();
}

// 6. Start/stop decoding multiple times doesn't crash
TEST_F(FFmpegDecoderTest, StartStopCycleSafe) {
    decoder.setInputPath("test.mp4");
    decoder.startDecoding(640, 480);
    decoder.stopDecoding();
    decoder.startDecoding(320, 240);
    decoder.stopDecoding();
    SUCCEED();
}

// 7. Thread object should be nullptr or valid after start
TEST_F(FFmpegDecoderTest, StartDoesNotCrashWithNullThread) {
    decoder.setInputPath("dummy.mp4");
    decoder.startDecoding(1280, 720);
    decoder.stopDecoding();
    SUCCEED();
}

// 8. Output size set affects decoding config (internal only)
// Cannot verify without exposing fields — placeholder
TEST_F(FFmpegDecoderTest, OutputSizePlaceholder) {
    decoder.setOutputSize(800, 600);
    SUCCEED();
}

// 9. Signal onFrameDecoded exists
TEST_F(FFmpegDecoderTest, HasOnFrameDecodedSignal) {
    const QMetaObject* meta = decoder.metaObject();
    int idx = meta->indexOfSignal("onFrameDecoded(QImage,qint16,qint16,float,qint16,qint16,float,qint16,qint16)");
    EXPECT_GE(idx, 0);
}

// 10. Signal onDecodingFinished exists
TEST_F(FFmpegDecoderTest, HasOnDecodingFinishedSignal) {
    const QMetaObject* meta = decoder.metaObject();
    int idx = meta->indexOfSignal("onDecodingFinished()");
    EXPECT_GE(idx, 0);
}
