#ifndef DATABASE_H
#define DATABASE_H

#include <stdbool.h>
#include <time.h>

bool get_user_salt(const char *username, char *salt);
bool get_user_hash(const char *username, char *hash);
void log_attempt(time_t time, const char *ip_address, const char *password, bool success);


#endif 