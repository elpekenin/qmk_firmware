// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

extern "C" {
#include "xap.h"
#include "util.h"
}


using testing::_;

class XAP : public ::testing::Test {};

TEST_F(XAP, XAPSecureRoute) {
    xap_token_t token = 0x1234;
    // Try and jump to bootloader - should not work as keyboard is locked
    const uint8_t *data = { 0x01, 0x07 };
    EXPECT_FALSE(xap_receive(token, data, ARRAY_SIZE(data))) << "Secure route was used while locked";
}
