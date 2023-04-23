#include "hash.h"
#include "database.h"
#include <argon2.h>
#include <string.h>

#define T_COST 2
#define M_COST 65536
#define PARALLELISM 1

bool hash_password(const char *password, const char *salt, char *hash) {
    if (password == NULL || salt == NULL || hash == NULL) {
        return false;
    }

    if (strlen(password) == 0 || strlen(salt) != SALTLEN) {
        return false;
    }

    argon2id_hash_raw(T_COST, M_COST, PARALLELISM, password, strlen(password), salt, SALTLEN, hash, HASHLEN);
    return true;
}