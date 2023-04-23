#ifndef RATELIMIT_H
#define RATELIMIT_H

#define RATE_LIMIT 5        // Max login attempts allowed
#define RATE_LIMIT_TIME 60  // Time in seconds to wait after rate limit is hit

int is_rate_limited(char* username);
void increment_rate_limit(char* username);
void clear_rate_limit(char* username);

#endif
