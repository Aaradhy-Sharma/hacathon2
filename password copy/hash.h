#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdbool.h>

#define HASHLEN 32
#define SALTLEN 16

bool hash_password(const char *password, const char *salt, char *hash);

#endif