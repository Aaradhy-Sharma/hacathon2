#include "hash.h"
#include <stdio.h>
#include <string.h>
#include "ratelimit.h"
#include "verify.h"



int verify_user(char* username, char* password)
{
    // Check if user is rate-limited
    if (is_rate_limited(username))
    {
        return AUTH_RATE_LIMIT;
    }

    // Get user's hashed password and salt from the database
    char* hashed_password = get_hashed_password(username);
    char* salt = get_salt(username);

    // Hash the entered password with the user's salt
    char* entered_hash = hash_password(password, salt);

    // Compare the entered hash with the stored hash
    if (strcmp(hashed_password, entered_hash) == 0)
    {
        // Passwords match, authentication successful
        clear_rate_limit(username);
        return AUTH_SUCCESS;
    }
    else
    {
        // Passwords do not match, authentication failed
        increment_rate_limit(username);
        return AUTH_FAILURE;
    }
}
