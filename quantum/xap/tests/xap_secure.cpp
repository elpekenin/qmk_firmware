// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "xap.h"
#include "util.h" // for ARRAY_SIZE

using testing::_;
using testing::InSequence;

class XAP : public TestFixture {};

TEST_F(XAP, XAPSecureRoute) {
    xap_token_t token = 0x1234;
    // Try and remap the keycode on layer 0, row 0, col 0 with KC_NO(0, 0) - should not work as keyboard is locked
    const uint8_t *data = { 0x05, 0x03, 0, 0, 0, 0, 0 };
    xap_receive(token, data, ARRAY_SIZE(data))
}
