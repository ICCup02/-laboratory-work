#ifndef TST_TESTLAB9_H
#define TST_TESTLAB9_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "lockcontroller.h"
using namespace testing;
using ::testing::Return;

class MockIKeypad : public IKeypad {
 public:
  MOCK_METHOD(bool, isActive, (), (override));
  MOCK_METHOD(void, wait, (), (override));
  MOCK_METHOD(PasswordResponse, requestPassword, (), (override));
};

class MockILatch : public ILatch {
 public:
  MOCK_METHOD(bool, isActive, (), (override));
  MOCK_METHOD(DoorStatus, open, (), (override));
  MOCK_METHOD(DoorStatus, close, (), (override));
  MOCK_METHOD(DoorStatus, getDoorStatus, (), (override));
};


TEST(Calculator, Test1Wait)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(keypad, wait())
            .Times(1);
    lc.wait();
}

TEST(Calculator, Test2IsDoorOpen_lock)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));
    bool res = lc.isDoorOpen();
    EXPECT_FALSE(res);
}

TEST(Calculator, Test3IsDoorOpen_unlock)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));
    bool res = lc.isDoorOpen();
    EXPECT_TRUE(res);
}

TEST(Calculator, Test4UnlockDoor)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(latch, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    EXPECT_EQ(lc.unlockDoor(), DoorStatus::OPEN);
}

TEST(Calculator, Test5LockDoor)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(latch, close())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    EXPECT_EQ(lc.lockDoor(), DoorStatus::CLOSE);
}

TEST(Calculator, Test6HardWareCheckStatusOk)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(1)
            .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
            .Times(1)
            .WillOnce(Return(true));

    auto res = lc.hardWareCheck();
    EXPECT_EQ(res, HardWareStatus::OK);
}

TEST(Calculator, Test7HardWareCheck_error)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(nullptr, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    auto res = lc.hardWareCheck();
    EXPECT_EQ(res, HardWareStatus::ERROR);
}

TEST(Calculator, Test8HardWareCheck_error_2)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(false));

    auto res = lc.hardWareCheck();
    EXPECT_EQ(res, HardWareStatus::ERROR);
}

TEST(Calculator, Test9IsCorrectPassword)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    PasswordResponse ans;
    ans.status = PasswordResponse::Status::OK;
    ans.password = "0000";

    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(ans));

    auto res = lc.isCorrectPassword();
    EXPECT_TRUE(res);
}

TEST(Calculator, Test10IsCorrectPassword_error)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    PasswordResponse ans;
    ans.status = PasswordResponse::Status::OK;
    ans.password = "6666";

    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(ans));

    auto res = lc.isCorrectPassword();
    EXPECT_FALSE(res);
}

TEST(Calculator, Test11ResetPassword)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    PasswordResponse old_pass;
    old_pass.status = PasswordResponse::Status::OK;
    old_pass.password = "0000";

    PasswordResponse new_pass;
    new_pass.status = PasswordResponse::Status::OK;
    new_pass.password = "6666";

     EXPECT_CALL(keypad, requestPassword())
            .Times(2)
            .WillOnce(Return(old_pass))
            .WillOnce(Return(new_pass));

    lc.resetPassword();

    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(new_pass));

    auto res = lc.isCorrectPassword();
    EXPECT_TRUE(res);
}

TEST(Calculator, Test12ResetPassword_2)
{
    MockIKeypad keypad;
    MockILatch latch;
    LockController lc = LockController(&keypad, &latch);

    PasswordResponse old_pass;
    old_pass.status = PasswordResponse::Status::OK;
    old_pass.password = "6666";

    PasswordResponse default_pass;
    default_pass.status = PasswordResponse::Status::OK;
    default_pass.password = "0000";

    EXPECT_CALL(keypad, requestPassword())
            .Times(2)
            .WillOnce(Return(default_pass))
            .WillOnce(Return(old_pass));
    lc.resetPassword();


    PasswordResponse new_pass;
    new_pass.status = PasswordResponse::Status::OK;
    new_pass.password = "9999";

    EXPECT_CALL(keypad, requestPassword())
            .Times(2)
            .WillOnce(Return(old_pass))
            .WillOnce(Return(new_pass));
    lc.resetPassword();

    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(new_pass));

    auto res = lc.isCorrectPassword();
    EXPECT_TRUE(res);
}


#endif // TST_TESTLAB9_H
