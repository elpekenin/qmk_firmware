# Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
# SPDX-License-Identifier: GPL-2.0-or-later

# --------------------------------------------------------------------------------
# Keep this file, even if it is empty, as a marker that this folder contains tests
# --------------------------------------------------------------------------------

# Trigger CLI to generate XAP files
# Also allows adding a `xap.hjson` and testing if it works
KEYBOARD = handwired/onekey/rp2040
KEYMAP = xap
# cant get $(QMK_BIN) to work here for some reason
$(shell qmk compile -c -kb $(KEYBOARD) -km $(KEYMAP) > /dev/null 2>&1)

xap_common_DEFS :=
xap_common_SRC := \
	$(QUANTUM_PATH)/xap/xap.c
xap_common_INC := \
	$(QUANTUM_PATH)/xap
