#include <gtest/gtest.h>
#include "Media/mediaviewmodel.h"
#include "Media/mediasampleapi.h"

// Fixture for MediaViewModel
class MediaViewModelTest : public ::testing::Test {
protected:
    MediaModel* model = new MediaModel();
    MediaViewModel* viewModel = new MediaViewModel(model);

    QList<MediaModel::MediaData> sample = MediaSampleAPI::getSampleSongs();

    void TearDown() override {
        delete viewModel;
        delete model;
    }
};

// 1. Song display list is not empty
TEST_F(MediaViewModelTest, SongDisplayListNotEmpty) {
    auto list = viewModel->getSongDisplayList();
    EXPECT_FALSE(list.isEmpty());
}

// 2. Current song name matches model
TEST_F(MediaViewModelTest, CurrentSongMatchesModel) {
    EXPECT_EQ(viewModel->getCurrentSong(), model->getCurrentMedia().song);
}

// 3. Next song is initially empty
TEST_F(MediaViewModelTest, NextSongInitiallyEmpty) {
    EXPECT_TRUE(viewModel->getNextSong().isEmpty());
}

// 4. Can set and get current media via viewmodel
TEST_F(MediaViewModelTest, SetAndGetCurrentMedia) {
    auto track = sample[0];
    viewModel->setCurrentMedia(track.source, track.album, track.artist, track.song, track.duration, track.time);

    EXPECT_EQ(viewModel->getCurrentSong(), track.song);
    EXPECT_EQ(viewModel->getCurrentArtist(), track.artist);
    EXPECT_EQ(viewModel->getCurrentAlbum(), track.album);
    EXPECT_EQ(viewModel->getCurrentDurationRaw(), track.duration);
    EXPECT_EQ(viewModel->getCurrentTimeRaw(), track.time);
}

// 5. Can set and get next media
TEST_F(MediaViewModelTest, SetAndGetNextMedia) {
    auto track = sample[1];
    viewModel->setNextMedia(track.source, track.album, track.artist, track.song, track.duration, track.time);

    EXPECT_EQ(viewModel->getNextSong(), track.song);
    EXPECT_EQ(viewModel->getNextArtist(), track.artist);
    EXPECT_EQ(viewModel->getNextAlbum(), track.album);
}

// 6. Can update current time
TEST_F(MediaViewModelTest, UpdateCurrentTime) {
    viewModel->setCurrentTime(42);
    EXPECT_EQ(viewModel->getCurrentTimeRaw(), 42);
}

// 7. Converts duration to mm:ss format correctly
TEST_F(MediaViewModelTest, DurationStringFormat) {
    viewModel->setCurrentMedia(0, "", "", "", 65000, 65000); // 65 sec = 01:05
    EXPECT_EQ(viewModel->getCurrentTime(), "01:05");
}

// 8. Duration over an hour is still formatted as mm:ss (truncated)
TEST_F(MediaViewModelTest, DurationOverHourString) {
    viewModel->setCurrentMedia(0, "", "", "", 3723000, 0); // 3723 sec = 62 min 3 sec
    EXPECT_EQ(viewModel->getCurrentDuration(), "62:03");
}

// 9. Icon path is valid
TEST_F(MediaViewModelTest, CurrentSourceIconNotEmpty) {
    EXPECT_FALSE(viewModel->getCurrentSourceIcon().isEmpty());
}

// 10. Next source icon path is valid
TEST_F(MediaViewModelTest, NextSourceIconNotEmptyAfterSet) {
    auto track = sample[1];
    viewModel->setNextMedia(track.source, track.album, track.artist, track.song, track.duration, track.time);
    EXPECT_FALSE(viewModel->getNextSourceIcon().isEmpty());
}

// 11. getSongObject returns valid fields
TEST_F(MediaViewModelTest, GetSongObjectContainsCorrectFields) {
    QVariantMap obj = viewModel->getSongObject(0);
    EXPECT_TRUE(obj.contains("song"));
    EXPECT_TRUE(obj.contains("artist"));
    EXPECT_TRUE(obj.contains("duration"));
}

// 12. getSongObject handles out-of-range
TEST_F(MediaViewModelTest, GetSongObjectOutOfRangeReturnsEmpty) {
    QVariantMap obj = viewModel->getSongObject(9999);
    EXPECT_TRUE(obj.isEmpty());
}

// 13. Initial current source is AMAZON
TEST_F(MediaViewModelTest, InitialCurrentSourceIsAmazon) {
    EXPECT_EQ(viewModel->getCurrentSourceRaw(), MediaModel::AMAZON);
}

// 14. Setting current media updates raw values
TEST_F(MediaViewModelTest, SetCurrentMediaRawFields) {
    auto track = sample[0];
    viewModel->setCurrentMedia(track.source, track.album, track.artist, track.song, track.duration, track.time);

    EXPECT_EQ(viewModel->getCurrentDurationRaw(), track.duration);
    EXPECT_EQ(viewModel->getCurrentTimeRaw(), track.time);
}

// 15. setCurrentTime affects mm:ss formatted string
TEST_F(MediaViewModelTest, SetCurrentTimeAffectsString) {
    viewModel->setCurrentTime(123000); // 123 sec = 2 min 3 sec
    EXPECT_EQ(viewModel->getCurrentTime(), "02:03");
}

// 16. Default current time is valid string
TEST_F(MediaViewModelTest, CurrentTimeFormattedInitiallyValid) {
    EXPECT_TRUE(viewModel->getCurrentTime().contains(":"));
}

// 17. Current and next are independent
TEST_F(MediaViewModelTest, CurrentAndNextAreIndependent) {
    viewModel->setCurrentMedia(1, "", "", "A", 100, 0);
    viewModel->setNextMedia(2, "", "", "B", 100, 0);
    EXPECT_NE(viewModel->getCurrentSong(), viewModel->getNextSong());
}

// 18. Can change time without changing song
TEST_F(MediaViewModelTest, ChangingTimeDoesNotChangeSong) {
    QString original = viewModel->getCurrentSong();
    viewModel->setCurrentTime(500);
    EXPECT_EQ(viewModel->getCurrentSong(), original);
}

// 19. Empty next song returns valid empty string
TEST_F(MediaViewModelTest, NextSongInitiallyEmptyString) {
    EXPECT_EQ(viewModel->getNextSong(), "");
}

// 20. Can set empty string fields safely
TEST_F(MediaViewModelTest, CanSetEmptyStrings) {
    viewModel->setCurrentMedia(0, "", "", "", 0, 0);
    EXPECT_TRUE(viewModel->getCurrentSong().isEmpty());
}

// 21. Raw values match after setNextMedia
TEST_F(MediaViewModelTest, RawFieldsMatchNextTrack) {
    auto track = sample[1];
    viewModel->setNextMedia(track.source, track.album, track.artist, track.song, track.duration, track.time);

    EXPECT_EQ(viewModel->getNextSourceRaw(), track.source);
    EXPECT_EQ(viewModel->getNextDurationRaw(), track.duration);
    EXPECT_EQ(viewModel->getNextTimeRaw(), track.time);
}

// 22. Source icon path changes correctly
TEST_F(MediaViewModelTest, SourceIconChangesWithSource) {
    viewModel->setCurrentMedia(MediaModel::SPOTIFY, "", "", "", 0, 0);
    QString icon = viewModel->getCurrentSourceIcon();
    EXPECT_TRUE(icon.contains("spotify", Qt::CaseInsensitive));
}

// 23. Handles negative duration/time
TEST_F(MediaViewModelTest, NegativeTimeAndDurationHandled) {
    viewModel->setCurrentMedia(0, "", "", "", -500, -123);
    EXPECT_EQ(viewModel->getCurrentDurationRaw(), -500);
    EXPECT_EQ(viewModel->getCurrentTimeRaw(), -123);
}

// 24. Raw enums interpreted correctly
TEST_F(MediaViewModelTest, CurrentSourceEnumCorrect) {
    EXPECT_EQ(viewModel->getCurrentSourceRaw(), static_cast<qint8>(MediaModel::AMAZON));
}

// 25. getCurrentSource returns readable string
TEST_F(MediaViewModelTest, CurrentSourceIsReadableString) {
    EXPECT_EQ(viewModel->getCurrentSource(), "Amazon Music");
}

// 26. getNextSource returns readable string
TEST_F(MediaViewModelTest, NextSourceIsReadableString) {
    viewModel->setNextMedia(MediaModel::USB, "", "", "", 0, 0);
    EXPECT_EQ(viewModel->getNextSource(), "USB");
}

// 27. Can update both current and next rapidly
TEST_F(MediaViewModelTest, UpdateCurrentAndNextConsecutively) {
    viewModel->setCurrentMedia(MediaModel::APPLE, "", "", "A", 100, 10);
    viewModel->setNextMedia(MediaModel::SPOTIFY, "", "", "B", 200, 20);
    EXPECT_EQ(viewModel->getCurrentSong(), "A");
    EXPECT_EQ(viewModel->getNextSong(), "B");
}

// 28. Default values are consistent
TEST_F(MediaViewModelTest, DefaultsConsistentWithModel) {
    auto modelTrack = model->getCurrentMedia();
    EXPECT_EQ(viewModel->getCurrentSong(), modelTrack.song);
    EXPECT_EQ(viewModel->getCurrentDurationRaw(), modelTrack.duration);
}

// 29. Calling setCurrentTime repeatedly
TEST_F(MediaViewModelTest, SetCurrentTimeRepeatedly) {
    viewModel->setCurrentTime(100);
    viewModel->setCurrentTime(200);
    EXPECT_EQ(viewModel->getCurrentTimeRaw(), 200);
}

// 30. Model pointer is not null
TEST_F(MediaViewModelTest, ModelPointerIsValid) {
    EXPECT_NE(viewModel, nullptr);
    EXPECT_NE(model, nullptr);
}
