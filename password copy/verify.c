#include "verify.h"
#include "database.h"
#include "hash.h"
#include <string.h>

#define HASHLEN 32

bool verify(const char *username, const char *password) {
    char salt[SALTLEN];
    char stored_hash[HASHLEN];
    char entered_hash[HASHLEN];

    if (!get_user_salt(username, salt)) {
        return false;
    }

    if (!get_user_hash(username, stored_hash)) {
        return false;
    }

    if (!hash_password(password, salt, entered_hash)) {
        return false;
    }

    return memcmp(stored_hash, entered_hash, HASHLEN) == 0;
}
