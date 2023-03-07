// No pending (time-based state)

extern "C" {
#include "secure.h"
}

secure_status_t secure_status = SECURE_LOCKED;

extern "C" secure_status_t secure_get_status(void) {
    return secure_status;
}

extern "C" void secure_lock(void) {
    secure_status = SECURE_LOCKED;
}

extern "C" void secure_unlock(void) {
    secure_status = SECURE_UNLOCKED;
}

extern "C" void secure_request_unlock(void) {
    secure_status = SECURE_UNLOCKED;
}
