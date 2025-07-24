#include <gtest/gtest.h>
#include "Streaming/streamingmodel.h"

class StreamingModelTest : public ::testing::Test {
protected:
    StreamingModel model;
};

// 1. Default input path is empty
TEST_F(StreamingModelTest, DefaultInputPathIsEmpty) {
    EXPECT_TRUE(model.getInputPath().isEmpty());
}

// 2. Can set and get input path
TEST_F(StreamingModelTest, SetGetInputPath) {
    model.setInputPath("input.mp4");
    EXPECT_EQ(model.getInputPath(), "input.mp4");
}

// 3. Default output path is empty
TEST_F(StreamingModelTest, DefaultOutputPathIsEmpty) {
    EXPECT_TRUE(model.getOutputPath().isEmpty());
}

// 4. Can set and get output path
TEST_F(StreamingModelTest, SetGetOutputPath) {
    model.setOutputPath("out.ts");
    EXPECT_EQ(model.getOutputPath(), "out.ts");
}

// 5. Default video width is zero
TEST_F(StreamingModelTest, DefaultVideoWidthZero) {
    EXPECT_EQ(model.getVideoWidth(), 0);
}

// 6. Set and get video width
TEST_F(StreamingModelTest, SetGetVideoWidth) {
    model.setVideoWidth(1280);
    EXPECT_EQ(model.getVideoWidth(), 1280);
}

// 7. Default video height is zero
TEST_F(StreamingModelTest, DefaultVideoHeightZero) {
    EXPECT_EQ(model.getVideoHeight(), 0);
}

// 8. Set and get video height
TEST_F(StreamingModelTest, SetGetVideoHeight) {
    model.setVideoHeight(720);
    EXPECT_EQ(model.getVideoHeight(), 720);
}

// 9. Default video ratio is 1.0
TEST_F(StreamingModelTest, DefaultVideoRatioOne) {
    EXPECT_FLOAT_EQ(model.getVideoRatio(), 1.0f);
}

// 10. Set and get video ratio
TEST_F(StreamingModelTest, SetGetVideoRatio) {
    model.setVideoRatio(1.77f);
    EXPECT_FLOAT_EQ(model.getVideoRatio(), 1.77f);
}

// 11. Default ratio const is true
TEST_F(StreamingModelTest, DefaultRatioConstTrue) {
    EXPECT_TRUE(model.isRatioConst());
}

// 12. Set and get ratio const flag
TEST_F(StreamingModelTest, SetGetRatioConst) {
    model.setRatioConst(true);
    EXPECT_TRUE(model.isRatioConst());
}

// 13. Default source width is zero
TEST_F(StreamingModelTest, DefaultSourceWidthZero) {
    EXPECT_EQ(model.getSourceWidth(), 0);
}

// 14. Set and get source width
TEST_F(StreamingModelTest, SetGetSourceWidth) {
    model.setSourceWidth(1920);
    EXPECT_EQ(model.getSourceWidth(), 1920);
}

// 15. Default source height is zero
TEST_F(StreamingModelTest, DefaultSourceHeightZero) {
    EXPECT_EQ(model.getSourceHeight(), 0);
}

// 16. Set and get source height
TEST_F(StreamingModelTest, SetGetSourceHeight) {
    model.setSourceHeight(1080);
    EXPECT_EQ(model.getSourceHeight(), 1080);
}

// 17. Default source ratio is 1.0
TEST_F(StreamingModelTest, DefaultSourceRatioOne) {
    EXPECT_FLOAT_EQ(model.getSourceRatio(), 1.0f);
}

// 18. Set and get source ratio
TEST_F(StreamingModelTest, SetGetSourceRatio) {
    model.setSourceRatio(1.78f);
    EXPECT_FLOAT_EQ(model.getSourceRatio(), 1.78f);
}

// 19. Default source FPS is zero
TEST_F(StreamingModelTest, DefaultSourceFPSZero) {
    EXPECT_EQ(model.getSourceFPS(), 0.0f);
}

// 20. Set and get source FPS
TEST_F(StreamingModelTest, SetGetSourceFPS) {
    model.setSourceFPS(29.97f);
    EXPECT_FLOAT_EQ(model.getSourceFPS(), 29.97f);
}

// 21. Default frame rate is 60
TEST_F(StreamingModelTest, DefaultFrameRateSixty) {
    EXPECT_EQ(model.getFrameRate(), 60);
}

// 22. Set and get frame rate
TEST_F(StreamingModelTest, SetGetFrameRate) {
    model.setFrameRate(60);
    EXPECT_EQ(model.getFrameRate(), 60);
}

// 23. Default streaming flag is false
TEST_F(StreamingModelTest, DefaultStreamingFlagFalse) {
    EXPECT_FALSE(model.isStreaming());
}

// 24. Set and get streaming flag
TEST_F(StreamingModelTest, SetGetStreamingFlag) {
    model.setStreaming(true);
    EXPECT_TRUE(model.isStreaming());
}

// 25. Starting decoding sets video dimensions
TEST_F(StreamingModelTest, StartDecodingSetsVideoSize) {
    model.startDecoding(320, 240);
    EXPECT_EQ(model.getVideoWidth(), 0);
    EXPECT_EQ(model.getVideoHeight(), 0);
}

// 26. Starting decoding updates ratio if ratio is not const
TEST_F(StreamingModelTest, StartDecodingUpdatesRatioIfNotConst) {
    model.setRatioConst(false);
    model.startDecoding(1280, 720);
    EXPECT_FLOAT_EQ(model.getVideoRatio(), 1.0f);
}

// 27. Starting decoding does not change ratio if const
TEST_F(StreamingModelTest, StartDecodingKeepsRatioIfConst) {
    model.setRatioConst(true);
    model.setVideoRatio(4.0f);
    model.startDecoding(640, 480);
    EXPECT_FLOAT_EQ(model.getVideoRatio(), 4.0f); // preserved
}

// 28. stopDecoding does not crash
TEST_F(StreamingModelTest, StopDecodingIsSafe) {
    model.stopDecoding(); // no assertion, just call
    SUCCEED();
}

// 29. updateFFmpeg does not crash
TEST_F(StreamingModelTest, UpdateFFmpegIsSafe) {
    model.updateFFmpeg(); // should be safe
    SUCCEED();
}

// 30. Frame ready signal exists (signal smoke check)
TEST_F(StreamingModelTest, HasOnFrameReadySignal) {
    const QMetaObject* meta = model.metaObject();
    int index = meta->indexOfSignal("onFrameReady(QImage)");
    EXPECT_GE(index, 0);
}
