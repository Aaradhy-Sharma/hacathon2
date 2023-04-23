#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include "verify.h"
#include "hash.h"
#include "ratelimit.h"


int main()
{
    // Get user input (username and password)
    char username[100];
    char password[100];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Verify user credentials
    int auth_result = verify_user(username, password);

    // Handle authentication result
    if (auth_result == AUTH_SUCCESS)
    {
        printf("Authentication successful!\n");
    }
    else if (auth_result == AUTH_FAILURE)
    {
        printf("Authentication failed.\n");
    }
    else if (auth_result == AUTH_RATE_LIMIT)
    {
        printf("Too many login attempts. Please try again later.\n");
    }

    return 0;
}
