#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include "hash.h"
#include "ratelimit.h"
#include "verify.h"


#define SALT_LENGTH 16
#define MAX_USERNAME_LENGTH 50
#define PASSWORD_FILE "passwords.txt"

char* get_hashed_password(char* username)
{
    FILE* fp = fopen(PASSWORD_FILE, "r");
    if (fp == NULL)
    {
        printf("Error: could not open password file.\n");
        exit(1);
    }

    char buffer[MAX_USERNAME_LENGTH + SHA512_DIGEST_LENGTH*2 + 2];
    char* hashed_password = NULL;
    while (fgets(buffer, MAX_USERNAME_LENGTH + SHA512_DIGEST_LENGTH*2 + 2, fp) != NULL)
    {
        // Check if this line matches the given username
        char* colon = strchr(buffer, ':');
        if (colon != NULL)
        {
            int username_length = colon - buffer;
            if (strncmp(buffer, username, username_length) == 0)
            {
                // Extract the hashed password
                hashed_password = malloc(SHA512_DIGEST_LENGTH*2 + 1);
                strncpy(hashed_password, colon + 1, SHA512_DIGEST_LENGTH*2);
                hashed_password[SHA512_DIGEST_LENGTH*2] = '\0';
                break;
            }
        }
    }

    fclose(fp);
    return hashed_password;
}

char* get_salt(char* username)
{
    FILE* fp = fopen(PASSWORD_FILE, "r");
    if (fp == NULL)
    {
        printf("Error: could not open password file.\n");
        exit(1);
    }

    char buffer[MAX_USERNAME_LENGTH + SHA512_DIGEST_LENGTH*2 + 2];
    char* salt = NULL;
    while (fgets(buffer, MAX_USERNAME_LENGTH + SHA512_DIGEST_LENGTH*2 + 2, fp) != NULL)
    {
        // Check if this line matches the given username
        char* colon = strchr(buffer, ':');
        if (colon != NULL)
        {
            int username_length = colon - buffer;
            if (strncmp(buffer, username, username_length) == 0)
            {
                // Extract the salt
                salt = malloc(SALT_LENGTH + 1);
                strncpy(salt, colon + 1 + SHA512_DIGEST_LENGTH*2 + 1, SALT_LENGTH);
                salt[SALT_LENGTH] = '\0';
                break;
            }
        }
    }

    fclose(fp);
    return salt;
}

char* hash_password(char* password, char* salt)
{
    char* combined = malloc(strlen(password) + SALT_LENGTH + 1);
    strcpy(combined, password);
    strcat(combined, salt);

    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512((unsigned char*)combined, strlen(combined), hash);

    char* hashed_password = malloc(SHA512_DIGEST_LENGTH*2 + 1);
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
    {
        sprintf(&hashed_password[i*2], "%02x", hash[i]);
    }
    hashed_password[SHA512_DIGEST_LENGTH*2] = '\0';

    free(combined);

    return hashed_password;
}
