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
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MIKeypad, wait())
            .Times(1);
    LC.wait();
}

TEST(Calculator, Test2IsDoorOpen_lock)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MILatch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    ASSERT_FALSE(LC.isDoorOpen());
}

TEST(Calculator, Test3IsDoorOpen_unlock)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MILatch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    ASSERT_TRUE(LC.isDoorOpen());
}

TEST(Calculator, Test4UnlockDoor)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MILatch, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    ASSERT_EQ(LC.unlockDoor(), DoorStatus::OPEN);
}

TEST(Calculator, Test5LockDoor)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MILatch, close())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    ASSERT_EQ(LC.lockDoor(), DoorStatus::CLOSE);
}

TEST(Calculator, Test6HardWareCheckStatusOk)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MIKeypad, isActive())
            .Times(1)
            .WillOnce(Return(true));

    EXPECT_CALL(MILatch, isActive())
            .Times(1)
            .WillOnce(Return(true));

    ASSERT_EQ(LC.hardWareCheck(), HardWareStatus::OK);
}

TEST(Calculator, Test7HardWareCheck_error)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(nullptr, &MILatch);

    EXPECT_CALL(MIKeypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    EXPECT_CALL(MILatch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    ASSERT_EQ(LC.hardWareCheck(), HardWareStatus::ERROR);
}

TEST(Calculator, Test8HardWareCheck_error_2)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    EXPECT_CALL(MIKeypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    EXPECT_CALL(MILatch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(false));

    ASSERT_EQ(LC.hardWareCheck(), HardWareStatus::ERROR);
}

TEST(Calculator, Test9IsCorrectPassword)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    PasswordResponse PRes;
    PRes.status = PasswordResponse::Status::OK;
    PRes.password = "0000";

    EXPECT_CALL(MIKeypad, requestPassword())
            .Times(1)
            .WillOnce(Return(PRes));

    ASSERT_TRUE(LC.isCorrectPassword());
}

TEST(Calculator, Test10IsCorrectPassword_error)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    PasswordResponse PRes;
    PRes.status = PasswordResponse::Status::OK;
    PRes.password = "6666";

    EXPECT_CALL(MIKeypad, requestPassword())
            .Times(1)
            .WillOnce(Return(PRes));

    ASSERT_FALSE(LC.isCorrectPassword());
}

TEST(Calculator, Test11ResetPassword)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    PasswordResponse old_pass;
    old_pass.status = PasswordResponse::Status::OK;
    old_pass.password = "0000";

    PasswordResponse new_pass;
    new_pass.status = PasswordResponse::Status::OK;
    new_pass.password = "6666";

     EXPECT_CALL(MIKeypad, requestPassword())
            .Times(2)
            .WillOnce(Return(old_pass))
            .WillOnce(Return(new_pass));

    LC.resetPassword();

    EXPECT_CALL(MIKeypad, requestPassword())
            .Times(1)
            .WillOnce(Return(new_pass));

    ASSERT_TRUE( LC.isCorrectPassword());
}

TEST(Calculator, Test12ResetPassword_2)
{
    MockIKeypad MIKeypad;
    MockILatch MILatch;
    LockController LC = LockController(&MIKeypad, &MILatch);

    PasswordResponse DefPass, OldPass, NewPass;

    DefPass.status = PasswordResponse::Status::OK;
    OldPass.status = PasswordResponse::Status::OK;
    NewPass.status = PasswordResponse::Status::OK;

    DefPass.password = "0000";
    OldPass.password = "6666";
    NewPass.password = "9999";

    EXPECT_CALL(MIKeypad, requestPassword())
            .Times(5)
            .WillOnce(Return(DefPass))
            .WillOnce(Return(OldPass))
            .WillOnce(Return(OldPass))
            .WillOnce(Return(NewPass))
            .WillOnce(Return(NewPass));

    LC.resetPassword();
    LC.resetPassword();

    ASSERT_TRUE(LC.isCorrectPassword());
}


#endif // TST_TESTLAB9_H
