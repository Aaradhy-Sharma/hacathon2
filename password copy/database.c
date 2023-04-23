#include "database.h"
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

bool get_user_salt(const char *username, char *salt) {
    FILE *file = fopen("salt.txt", "r");
    if (file == NULL) {
        return false;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *line_username = strtok(line, ",");
        char *line_salt = strtok(NULL, ",");
        if (strcmp(line_username, username) == 0) {
            strcpy(salt, line_salt);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool get_user_hash(const char *username, char *hash) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return false;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *line_username = strtok(line, ",");
        char *line_password = strtok(NULL, ",");
        if (strcmp(line_username, username) == 0) {
            strcpy(hash, line_password);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

void log_attempt(time_t time, const char *ip_address, const char *password_attempted, bool success) {
    FILE *file = fopen("logs.txt", "a");
    if (file == NULL) {
        return;
    }

    fprintf(file, "%ld,%s,%s,%s\n", time, ip_address, password_attempted, success ? "success" : "failure");
    fclose(file);
}