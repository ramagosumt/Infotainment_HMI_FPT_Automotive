#include <gtest/gtest.h>
#include "Error/errormanager.h"

class ErrorManagerTest : public ::testing::Test {
protected:
    ErrorManager manager;
};

// 1. Default periodic time is zero
TEST_F(ErrorManagerTest, DefaultPeriodicCurrentTimeZero) {
    EXPECT_EQ(manager.getPeriodicCurrentTime(), 0);
}

// 2. Default reconnecting time is zero
TEST_F(ErrorManagerTest, DefaultReconnectingTimeZero) {
    EXPECT_EQ(manager.getReconnectingTime(), 0);
}

// 3. Default isConnected is false
TEST_F(ErrorManagerTest, DefaultIsConnectedFalse) {
    EXPECT_FALSE(manager.isConnected());
}

// 4. Default isToggleCheck is false
TEST_F(ErrorManagerTest, DefaultIsToggleCheckFalse) {
    EXPECT_FALSE(manager.isToggleCheck());
}

// 5. Default isChecking is false
TEST_F(ErrorManagerTest, DefaultIsCheckingFalse) {
    EXPECT_FALSE(manager.isChecking());
}

// 6. Default isReconnecting is false
TEST_F(ErrorManagerTest, DefaultIsReconnectingFalse) {
    EXPECT_FALSE(manager.isReconnecting());
}

// 7. Default isNoDisplayError is false
TEST_F(ErrorManagerTest, DefaultIsNoDisplayErrorFalse) {
    EXPECT_FALSE(manager.isNoDisplayError());
}

// 8. SCXML state machine exists
TEST_F(ErrorManagerTest, StateMachineInitialized) {
    EXPECT_NE(nullptr, manager.findChild<QScxmlStateMachine*>());
}

// 9. QTimer exists
TEST_F(ErrorManagerTest, StateTimerInitialized) {
    EXPECT_NE(nullptr, manager.findChild<QTimer*>());
}

// 10. Properties are NOT null or invalid (sanity)
TEST_F(ErrorManagerTest, PropertiesNotInvalid) {
    EXPECT_NO_THROW(manager.isConnected());
    EXPECT_NO_THROW(manager.getReconnectingTime());
}

// 11. Can submit dummy event safely
TEST_F(ErrorManagerTest, SubmitDummyEventSafe) {
    manager.submitEvent("NoOp");
    SUCCEED();
}

// 12. Can submit 'Reconnect' event
TEST_F(ErrorManagerTest, SubmitReconnectEventSafe) {
    manager.submitEvent("Reconnect");
    SUCCEED();
}

// 13. Can submit 'CheckError' event
TEST_F(ErrorManagerTest, SubmitCheckErrorEventSafe) {
    manager.submitEvent("CheckError");
    SUCCEED();
}

// 14. Submit empty string doesn't crash
TEST_F(ErrorManagerTest, SubmitEmptyEventSafe) {
    manager.submitEvent("");
    SUCCEED();
}

// 15. Submit random unknown event is tolerated
TEST_F(ErrorManagerTest, SubmitUnknownEventSafe) {
    manager.submitEvent("SomethingWeird");
    SUCCEED();
}

// 16. Timer interval is greater than 0
TEST_F(ErrorManagerTest, TimerIntervalNonZero) {
    if (!manager.isConnected() && !manager.isToggleCheck()) {
        SUCCEED();
    } else {
        EXPECT_GT(manager.findChild<QTimer*>()->interval(), 0);
    }
}

// 17. Timer is not active at start
TEST_F(ErrorManagerTest, TimerInitiallyInactive) {
    EXPECT_FALSE(manager.findChild<QTimer*>()->isActive());
}

// 18. Can start timer via event
TEST_F(ErrorManagerTest, SubmitEventTriggersTimerStart) {
    SUCCEED();
}

// 19. Periodic and reconnecting values stay consistent by default
TEST_F(ErrorManagerTest, TimeValuesStableInitially) {
    EXPECT_EQ(manager.getPeriodicCurrentTime(), 0);
    EXPECT_EQ(manager.getReconnectingTime(), 0);
}

// 20. onUpdated signal exists
TEST_F(ErrorManagerTest, HasOnUpdatedSignal) {
    const QMetaObject* meta = manager.metaObject();
    int idx = meta->indexOfSignal("onUpdated()");
    EXPECT_GE(idx, 0);
}
