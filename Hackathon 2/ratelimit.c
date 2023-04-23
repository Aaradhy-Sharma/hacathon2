#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ratelimit.h"


struct rate_limit
{
    char* username;
    int attempts;
    time_t reset_time;
};

struct rate_limit* rate_limits = NULL;
int num_rate_limits = 0;

int is_rate_limited(char* username)
{
    // Search for existing rate limit for this user
    for (int i = 0; i < num_rate_limits; i++)
    {
        if (strcmp(rate_limits[i].username, username) == 0)
        {
            // Found existing rate limit for this user
            time_t current_time = time(NULL);
            if (current_time < rate_limits[i].reset_time)
            {
                // Rate limit is still active
                return 1;
            }
            else
            {
                // Rate limit has expired, clear it
                rate_limits[i].attempts = 0;
                return 0;
            }
        }
    }

    // No rate limit exists for this user, create a new one
    struct rate_limit new_rate_limit;
    new_rate_limit.username = malloc(strlen(username) + 1);
    strcpy(new_rate_limit.username, username);
    new_rate_limit.attempts = 0;
    new_rate_limit.reset_time = 0;
    rate_limits = realloc(rate_limits, sizeof(struct rate_limit) * (num_rate_limits + 1));
    rate_limits[num_rate_limits] = new_rate_limit;
    num_rate_limits++;

    return 0;
}

void increment_rate_limit(char* username)
{
    // Search for existing rate limit for this user
    for (int i = 0; i < num_rate_limits; i++)
    {
        if (strcmp(rate_limits[i].username, username) == 0)
        {
            // Found existing rate limit for this user
            rate_limits[i].attempts++;
            if (rate_limits[i].attempts >= RATE_LIMIT)
            {
                // User has hit the rate limit, set reset time
                rate_limits[i].reset_time = time(NULL) + RATE_LIMIT_TIME;
            }
            return;
        }
    }

    // No rate limit exists for this user, create a new one
    struct rate_limit new_rate_limit;
    new_rate_limit.username = malloc(strlen(username) + 1);
    strcpy(new_rate_limit.username, username);
    new_rate_limit.attempts = 1;
    new_rate_limit.reset_time = 0;
    rate_limits = realloc(rate_limits, sizeof(struct rate_limit) * (num_rate_limits + 1));
    rate_limits[num_rate_limits] = new_rate_limit;
    num_rate_limits++;
}

void clear_rate_limit(char* username)
{
    // Search for existing rate limit for this user
    for (int i = 0; i < num_rate_limits; i++)
    {
        if (strcmp(rate_limits[i].username, username) == 0)
        {
            // Found existing rate limit for this user, clear it
            rate_limits[i].attempts = 0;
            rate_limits[i].reset_time = 0;
            return;
        }
    }
}
