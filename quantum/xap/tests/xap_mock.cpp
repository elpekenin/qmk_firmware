#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"

extern "C" {
#include "xap.h"
}

// We wont be sending any data, so these can just be no-ops

extern "C" void xap_broadcast(uint8_t type, const void *data, size_t length) {}

extern "C" void xap_respond_failure(xap_token_t token, xap_response_flags_t response_flags) {}

extern "C" bool xap_respond_data(xap_token_t token, const void *data, size_t length) {}

extern "C" bool xap_respond_data_P(xap_token_t token, const void *data, size_t length) {}
