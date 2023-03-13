#include <stdio.h>
#include <ctype.h>

#include "include/ANSI_Colors.h"
#include "include/Cipher.h"
#include "include/RandomGenerator.h"
#include "include/KeyboardListener.h"
#include "include/SHA-512.h"
#include "include/Util.h"

char *encryption_round_1;
char *encryption_round_2;
char *encrypted;

char *decryption_round_1;
char *decryption_round_2;
char *decrypted;


int main(int argc, char *argv[]) {

    clear();
    char *text = argv[1] ? argv[1] : "Hello World!";
    char *key = generate_key(20);

    uint8_t digest[64];
	sha512((const uint8_t*)key, strlen(key), digest);
 
	char hashed_key[128] = { 0 };
	for (size_t i = 0; i < 64; i++)
		sprintf(hashed_key + i * 2, "%02x", digest[i]);

    encryption_round_1 = enc(text, hashed_key);
    encryption_round_2 = enc(encryption_round_1, hashed_key);
    encrypted = enc(encryption_round_2, hashed_key);

    decryption_round_1 = dec(encrypted, hashed_key);
    decryption_round_2 = dec(decryption_round_1, hashed_key);
    decrypted = dec(decryption_round_2, hashed_key);
    
    printf("%sText       %s: %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, text);
    printf("%sKey        %s: %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, key);
    printf("%sHashed Key %s: %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, hashed_key);
    printf("%sEncrypted  %s: %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, encrypted);
    printf("%sDecrypted  %s: %s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET, decrypted);

    free(key);
    free(encrypted);
    free(decrypted);

    getchar();
    printf("Press any key to exit...");
    waitKey();
    
    return 0;
}