#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "verify.h"
#include "ratelimit.h"

int main() {
    char ip_address[256] = "192.168.1.1"; // This would normally be obtained from the user's network connection
    char username[256];
    char password[256];

    if (!check_ratelimit(ip_address)) {
        printf("Too many login attempts. Please try again later.\n");
        return 0;
    }

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    if (verify(username, password)) {
        printf("Login successful!\n");
        log_attempt(time(NULL), ip_address, password, true);
    } else {
        printf("Invalid username or password.\n");
        log_attempt(time(NULL), ip_address, password, false);
    }

    return 0;
}