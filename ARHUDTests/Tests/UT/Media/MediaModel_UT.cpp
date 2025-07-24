#include <gtest/gtest.h>
#include "Media/mediamodel.h"
#include "Media/mediasampleapi.h"

class MediaModelTest : public ::testing::Test {
protected:
    MediaModel model;
    QList<MediaModel::MediaData> sample = MediaSampleAPI::getSampleSongs();
};

// 1. Current media is from API by default
TEST_F(MediaModelTest, DefaultCurrentMediaIsFromSample) {
    auto current = model.getCurrentMedia();
    EXPECT_EQ(current.song, "3107");
    EXPECT_EQ(current.artist, "Duongg");
    EXPECT_EQ(current.duration, 227000);
}

// 2. Next media is empty by default
TEST_F(MediaModelTest, DefaultNextMediaIsEmpty) {
    auto next = model.getNextMedia();
    EXPECT_TRUE(next.artist.isEmpty());
    EXPECT_EQ(next.time, 0);
}

// 3. Can set and get current media
TEST_F(MediaModelTest, SetGetCurrentMedia) {
    auto track = sample[0];
    model.setCurrentMedia(track);
    auto current = model.getCurrentMedia();

    EXPECT_EQ(current.source, track.source);
    EXPECT_EQ(current.album, track.album);
    EXPECT_EQ(current.artist, track.artist);
    EXPECT_EQ(current.song, track.song);
    EXPECT_EQ(current.duration, track.duration);
    EXPECT_EQ(current.time, track.time);
}

// 4. Can set and get next media
TEST_F(MediaModelTest, SetGetNextMedia) {
    auto track = sample[1];
    model.setNextMedia(track);
    auto next = model.getNextMedia();

    EXPECT_EQ(next.source, track.source);
    EXPECT_EQ(next.album, track.album);
    EXPECT_EQ(next.artist, track.artist);
    EXPECT_EQ(next.song, track.song);
    EXPECT_EQ(next.duration, track.duration);
    EXPECT_EQ(next.time, track.time);
}

// 5. Different tracks can be set for current and next
TEST_F(MediaModelTest, IndependentCurrentAndNextMedia) {
    auto current = sample[0];
    auto next = sample[1];

    model.setCurrentMedia(current);
    model.setNextMedia(next);

    EXPECT_EQ(model.getCurrentMedia().song, current.song);
    EXPECT_EQ(model.getNextMedia().song, next.song);
    EXPECT_NE(model.getCurrentMedia().song, next.song);
}

// 6. Handles empty strings correctly
TEST_F(MediaModelTest, AcceptsEmptyFields) {
    MediaModel::MediaData blank;
    blank.source = MediaModel::UNSPECIFIED;
    blank.duration = 0;
    blank.time = 0;

    model.setCurrentMedia(blank);
    auto current = model.getCurrentMedia();

    EXPECT_TRUE(current.album.isEmpty());
    EXPECT_EQ(current.source, MediaModel::UNSPECIFIED);
}

// 7. Preserves special characters in metadata
TEST_F(MediaModelTest, AcceptsUnicodeFields) {
    MediaModel::MediaData track;
    track.song = "夜に駆ける";
    track.artist = "YOASOBI";
    track.album = "夜に駆ける";
    track.source = MediaModel::SPOTIFY;

    model.setCurrentMedia(track);
    EXPECT_EQ(model.getCurrentMedia().artist, "YOASOBI");
}

// 8. Negative duration is preserved as-is
TEST_F(MediaModelTest, HandlesNegativeDuration) {
    MediaModel::MediaData track;
    track.song = "Corrupt Data";
    track.duration = -99;
    model.setCurrentMedia(track);

    EXPECT_EQ(model.getCurrentMedia().duration, -99);
}

// 9. Can update media time separately
TEST_F(MediaModelTest, CanUpdateTime) {
    auto track = sample[0];
    track.time = 120;
    model.setCurrentMedia(track);

    EXPECT_EQ(model.getCurrentMedia().time, 120);
}

// 10. Media source enum behaves as expected
TEST_F(MediaModelTest, MediaSourceEnum) {
    EXPECT_EQ(static_cast<int>(MediaModel::SPOTIFY), 4);
    EXPECT_EQ(static_cast<int>(MediaModel::USB), 5);
}

// 11. Setting same media twice is idempotent
TEST_F(MediaModelTest, SettingSameTrackTwice) {
    auto track = sample[0];
    model.setCurrentMedia(track);
    model.setCurrentMedia(track);

    EXPECT_EQ(model.getCurrentMedia().song, track.song);
}

// 12. Default source is AMAZON
TEST_F(MediaModelTest, DefaultSourceIsAmazonFromSample) {
    auto current = model.getCurrentMedia();
    EXPECT_EQ(current.source, MediaModel::AMAZON);
}


// 13. Next media override replaces previous value
TEST_F(MediaModelTest, NextMediaOverridesCorrectly) {
    model.setNextMedia(sample[0]);
    model.setNextMedia(sample[1]);
    EXPECT_EQ(model.getNextMedia().song, sample[1].song);
}

// 14. Setting duration doesn’t affect strings
TEST_F(MediaModelTest, DurationDoesNotAffectStrings) {
    MediaModel::MediaData data = model.getCurrentMedia();
    data.duration = 999999;
    model.setCurrentMedia(data);

    EXPECT_FALSE(model.getCurrentMedia().song.isEmpty());
}

// 15. Songs from sample API are non-empty
TEST_F(MediaModelTest, SampleSongsNonEmpty) {
    const auto& songs = MediaSampleAPI::getSampleSongs();
    ASSERT_FALSE(songs.isEmpty());

    for (const auto& song : songs) {
        if (song.source == MediaModel::UNSPECIFIED && song.song.isEmpty() && song.artist.isEmpty())
            continue; // intentionally blank entry
        EXPECT_FALSE(song.song.isEmpty() && song.artist.isEmpty());
    }
}

// 16. Accepts Amazon as Source
TEST_F(MediaModelTest, AcceptsAmazonSource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::AMAZON;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::AMAZON);
}

// 17. Accepts Apple as Source
TEST_F(MediaModelTest, AcceptsAppleSource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::APPLE;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::APPLE);
}

// 18. Accepts Radio as Source
TEST_F(MediaModelTest, AcceptsRadioSource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::RADIO;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::RADIO);
}

// 19. Accepts SoundCloud as Source
TEST_F(MediaModelTest, AcceptsSoundCloudSource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::SOUNDCLOUD;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::SOUNDCLOUD);
}

// 20. Accepts Spotify as Source
TEST_F(MediaModelTest, AcceptsSpotifySource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::SPOTIFY;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::SPOTIFY);
}

// 21. Accepts USB as Source
TEST_F(MediaModelTest, AcceptsUSBSource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::USB;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::USB);
}

// 22. Accepts Unspecified as Source
TEST_F(MediaModelTest, AcceptsUnspecifiedSource) {
    MediaModel::MediaData data = sample[0];
    data.source = MediaModel::UNSPECIFIED;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().source, MediaModel::UNSPECIFIED);
}

// 23. Set both current and next media independently
TEST_F(MediaModelTest, CurrentNextMediaAreIndependent) {
    model.setCurrentMedia(sample[0]);
    model.setNextMedia(sample[1]);
    EXPECT_EQ(model.getCurrentMedia().song, sample[0].song);
    EXPECT_EQ(model.getNextMedia().song, sample[1].song);
}

// 24. Changing current media doesn't affect next
TEST_F(MediaModelTest, CurrentChangeDoesNotAffectNext) {
    model.setNextMedia(sample[1]);
    model.setCurrentMedia(sample[0]);
    EXPECT_EQ(model.getNextMedia().song, sample[1].song);
}

// 25. Duration can be zero
TEST_F(MediaModelTest, AcceptsZeroDuration) {
    MediaModel::MediaData data = sample[0];
    data.duration = 0;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().duration, 0);
}

// 26. Time can be zero
TEST_F(MediaModelTest, AcceptsZeroTime) {
    MediaModel::MediaData data = sample[0];
    data.time = 0;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().time, 0);
}

// 27. Duration can be negative (no validation)
TEST_F(MediaModelTest, AcceptsNegativeDuration) {
    MediaModel::MediaData data = sample[0];
    data.duration = -99;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().duration, -99);
}

// 28. Time can be negative (no validation)
TEST_F(MediaModelTest, AcceptsNegativeTime) {
    MediaModel::MediaData data = sample[0];
    data.time = -42;
    model.setCurrentMedia(data);
    EXPECT_EQ(model.getCurrentMedia().time, -42);
}

// 29. Can override all values at once
TEST_F(MediaModelTest, OverrideAllValuesInMediaData) {
    MediaModel::MediaData data;
    data.source = MediaModel::RADIO;
    data.album = "Best Of";
    data.artist = "Unknown";
    data.song = "Mystery";
    data.duration = 300;
    data.time = 42;

    model.setCurrentMedia(data);
    MediaModel::MediaData out = model.getCurrentMedia();

    EXPECT_EQ(out.source, MediaModel::RADIO);
    EXPECT_EQ(out.album, "Best Of");
    EXPECT_EQ(out.artist, "Unknown");
    EXPECT_EQ(out.song, "Mystery");
    EXPECT_EQ(out.duration, 300);
    EXPECT_EQ(out.time, 42);
}

// 30. MediaModel defaults to Sample API
TEST_F(MediaModelTest, DefaultMediaIsSampleSongNotEmpty) {
    const auto& d = model.getCurrentMedia();
    EXPECT_EQ(d.source, MediaModel::AMAZON);
    EXPECT_FALSE(d.artist.isEmpty());
    EXPECT_FALSE(d.song.isEmpty());
    EXPECT_GT(d.duration, 0);
}
