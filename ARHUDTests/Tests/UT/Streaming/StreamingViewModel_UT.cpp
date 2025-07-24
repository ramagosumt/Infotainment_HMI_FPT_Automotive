#include <gtest/gtest.h>
#include "Streaming/streamingviewmodel.h"

class StreamingViewModelTest : public ::testing::Test {
protected:
    StreamingModel* model = new StreamingModel();
    StreamingViewModel* viewModel = new StreamingViewModel(model);

    void TearDown() override {
        delete viewModel;
        delete model;
    }
};

// 1. Default input path is empty
TEST_F(StreamingViewModelTest, DefaultInputPathIsEmpty) {
    EXPECT_TRUE(viewModel->getInputPath().isEmpty());
}

// 2. Default output path is empty
TEST_F(StreamingViewModelTest, DefaultOutputPathIsEmpty) {
    EXPECT_TRUE(viewModel->getOutputPath().isEmpty());
}

// 3. Default video width is 0
TEST_F(StreamingViewModelTest, DefaultVideoWidthIsZero) {
    EXPECT_EQ(viewModel->getVideoWidth(), 0);
}

// 4. Default video height is 0
TEST_F(StreamingViewModelTest, DefaultVideoHeightIsZero) {
    EXPECT_EQ(viewModel->getVideoHeight(), 0);
}

// 5. Default video ratio is 1.0
TEST_F(StreamingViewModelTest, DefaultVideoRatioIsOne) {
    EXPECT_FLOAT_EQ(viewModel->getVideoRatio(), 1.0f);
}

// 6. Default ratio const is true
TEST_F(StreamingViewModelTest, DefaultRatioConstIsTrue) {
    EXPECT_TRUE(viewModel->isRatioConst());
}

// 7. Default frame rate is 60
TEST_F(StreamingViewModelTest, DefaultFrameRateIsSixty) {
    EXPECT_EQ(viewModel->getFrameRate(), 60);
}

// 8. Default isStreaming is false
TEST_F(StreamingViewModelTest, DefaultStreamingIsFalse) {
    EXPECT_FALSE(viewModel->isStreaming());
}

// 9. Default source width is 0
TEST_F(StreamingViewModelTest, DefaultSourceWidthIsZero) {
    EXPECT_EQ(viewModel->getSourceWidth(), 0);
}

// 10. Default source height is 0
TEST_F(StreamingViewModelTest, DefaultSourceHeightIsZero) {
    EXPECT_EQ(viewModel->getSourceHeight(), 0);
}

// 11. Default source ratio is 1.0
TEST_F(StreamingViewModelTest, DefaultSourceRatioIsOne) {
    EXPECT_FLOAT_EQ(viewModel->getSourceRatio(), 1.0f);
}

// 12. Default source FPS is 0
TEST_F(StreamingViewModelTest, DefaultSourceFPSIsZero) {
    EXPECT_EQ(viewModel->getSourceFPS(), 0);
}

// 13. Default current frame is null
TEST_F(StreamingViewModelTest, DefaultCurrentFrameIsNull) {
    EXPECT_TRUE(viewModel->getCurrentFrame().isNull());
}

// 14. Can set output path
TEST_F(StreamingViewModelTest, SetOutputPath) {
    viewModel->setOutputPath("output.ts");
    EXPECT_EQ(viewModel->getOutputPath(), "output.ts");
}

// 15. Can set video width
TEST_F(StreamingViewModelTest, SetVideoWidth) {
    viewModel->setVideoWidth(640);
    EXPECT_EQ(viewModel->getVideoWidth(), 640);
}

// 16. Can set video height
TEST_F(StreamingViewModelTest, SetVideoHeight) {
    viewModel->setVideoHeight(480);
    EXPECT_EQ(viewModel->getVideoHeight(), 480);
}

// 17. Can set video ratio
TEST_F(StreamingViewModelTest, SetVideoRatio) {
    viewModel->setVideoRatio(1.5f);
    EXPECT_FLOAT_EQ(viewModel->getVideoRatio(), 1.5f);
}

// 18. Can set ratio const
TEST_F(StreamingViewModelTest, SetRatioConst) {
    viewModel->setRatioConst(false);
    EXPECT_FALSE(viewModel->isRatioConst());
}

// 19. Can set frame rate
TEST_F(StreamingViewModelTest, SetFrameRate) {
    viewModel->setFrameRate(30);
    EXPECT_EQ(viewModel->getFrameRate(), 30);
}

// 20. Can set isStreaming
TEST_F(StreamingViewModelTest, SetIsStreaming) {
    viewModel->setIsStreaming(true);
    EXPECT_TRUE(viewModel->isStreaming());
}

// 21. Can set source width
TEST_F(StreamingViewModelTest, SetSourceWidth) {
    viewModel->setSourceWidth(1024);
    EXPECT_EQ(viewModel->getSourceWidth(), 1024);
}

// 22. Can set source height
TEST_F(StreamingViewModelTest, SetSourceHeight) {
    viewModel->setSourceHeight(768);
    EXPECT_EQ(viewModel->getSourceHeight(), 768);
}

// 23. Can set source ratio
TEST_F(StreamingViewModelTest, SetSourceRatio) {
    viewModel->setSourceRatio(1.33f);
    EXPECT_FLOAT_EQ(viewModel->getSourceRatio(), 1.33f);
}

// 24. Can set source FPS
TEST_F(StreamingViewModelTest, SetSourceFPS) {
    viewModel->setSourceFPS(24);
    EXPECT_EQ(viewModel->getSourceFPS(), 24);
}

// 25. Can set input path and decode safely
TEST_F(StreamingViewModelTest, SetInputPathAndStart) {
    viewModel->setInputPath("sample.mp4");
    viewModel->startDecoding(1280, 720);
    EXPECT_TRUE(viewModel->isStreaming());
}

// 26. stopDecoding sets streaming to false
TEST_F(StreamingViewModelTest, StopDecodingSetsStreamingFalse) {
    viewModel->setInputPath("sample.mp4");
    viewModel->startDecoding(1280, 720);
    viewModel->stopDecoding();
    EXPECT_FALSE(viewModel->isStreaming());
}

// 27. startDecoding with empty path does not crash
TEST_F(StreamingViewModelTest, StartWithEmptyPathDoesNothing) {
    viewModel->startDecoding(800, 600);
    EXPECT_FALSE(viewModel->isStreaming());
}

// 28. Calling decoder signal manually updates current frame
TEST_F(StreamingViewModelTest, ModelFrameUpdatesCurrentFrame) {
    QImage img(160, 90, QImage::Format_RGB32);
    emit model->onFrameReady(img);  // simulate frame arrival
    EXPECT_EQ(viewModel->getCurrentFrame().width(), 160);
    EXPECT_EQ(viewModel->getCurrentFrame().height(), 90);
}

// 29. setInputPath updates internal model
TEST_F(StreamingViewModelTest, InputPathReflectsAfterSet) {
    viewModel->setInputPath("media/test.mp4");
    EXPECT_EQ(viewModel->getInputPath(), "media/test.mp4");
    EXPECT_EQ(model->getInputPath(), "media/test.mp4");
}

// 30. setVideoRatio reflects change immediately
TEST_F(StreamingViewModelTest, VideoRatioUpdatesModelAndView) {
    viewModel->setVideoRatio(2.0f);
    EXPECT_FLOAT_EQ(viewModel->getVideoRatio(), 2.0f);
    EXPECT_FLOAT_EQ(model->getVideoRatio(), 2.0f);
}
