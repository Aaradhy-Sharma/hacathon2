#ifndef HASH_H
#define HASH_H

char* hash_password(char* password, char* salt);
char* generate_salt();
char* get_hashed_password(char* username);
char* get_salt(char* username);


#endif /* HASH_H */
