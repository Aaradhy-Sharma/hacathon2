#ifndef RATELIMIT_H
#define RATELIMIT_H

#include <stdbool.h>

bool check_ratelimit(const char *ip_address);

#endif