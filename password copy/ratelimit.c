#include "ratelimit.h"
#include "database.h"

#define MAX_ATTEMPTS 5

bool check_ratelimit(const char *ip_address) {
    int attempts = get_login_attempts(ip_address);

    if (attempts >= MAX_ATTEMPTS) {
        return false;
    }

    increment_login_attempts(ip_address);
    return true;
}