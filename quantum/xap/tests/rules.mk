# Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
# SPDX-License-Identifier: GPL-2.0-or-later

# --------------------------------------------------------------------------------
# Keep this file, even if it is empty, as a marker that this folder contains tests
# --------------------------------------------------------------------------------

KEYBOARD = handwired/onekey/rp2040
KEYMAP = xap
include $(BUILDDEFS_PATH)/xap.mk

xap_secure_DEFS :=
xap_secure_SRC :=
xap_secure_INC := \
	$(QUANTUM_PATH)/xap
