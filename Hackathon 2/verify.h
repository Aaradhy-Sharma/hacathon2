#ifndef VERIFY_H
#define VERIFY_H

// Constants for authentication results
#define AUTH_SUCCESS 0
#define AUTH_FAILURE 1
#define AUTH_RATE_LIMIT 2

// Function prototypes
int verify_user(char* username, char* password);

#endif /* VERIFY_H */
