// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

extern "C" {
#include "xap.h"
}

#include "gtest/gtest.h"

class XAP : public ::testing::Test {};

TEST_F(XAP, NonSecureRouteAvailable) {
    xap_token_t token = 0x1234;
    // Try and use non-secure route - should work regardless of lock state
    const uint8_t msg[] = { 0x00, 0x00 }; // XAP protocol version query
    EXPECT_TRUE(xap_receive(token, msg, sizeof(msg))) << "Non-secure route couldn't be used";
}

TEST_F(XAP, SecureRouteLocked) {
    xap_token_t token = 0x1234;
    // Try and use secure route - should not work as keyboard is locked
    const uint8_t msg[] = { 0x05, 0x03 }; // Remap key
    EXPECT_FALSE(xap_receive(token, msg, sizeof(msg))) << "Secure route was used while locked";
}
