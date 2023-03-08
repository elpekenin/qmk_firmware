// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

extern "C" {
#include "secure.h"
#include "xap.h"
}

#include "gtest/gtest.h"

class XAP : public ::testing::Test {};

xap_token_t token = 0x1234;

// Just a convenience wrapper
#define xap_test(msg) xap_receive(token, msg, sizeof(msg))

TEST_F(XAP, NonSecureLocked) {
    // Try and use non-secure route while locked
    secure_lock();
    const uint8_t msg[] = { 0x00, 0x00 }; // XAP protocol version query
    EXPECT_TRUE(xap_test(msg)) << "Non-secure route couldn't be used";
}

TEST_F(XAP, SecureLocked) {
    // Try and use secure route while locked
    secure_lock();
    const uint8_t msg[] = { 0x01, 0x07 }; // Bootloader jump
    EXPECT_FALSE(xap_test(msg)) << "Secure route was used while locked";
}

TEST_F(XAP, SecureUnlocked) {
    // Try and use secure route after unlocking
    secure_unlock();
    const uint8_t msg[] = { 0x01, 0x07 }; // Bootloader jump
    EXPECT_TRUE(xap_test(msg)) << "Secure route couldn't be used while unlocked";
}
