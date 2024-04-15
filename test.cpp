#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blake2.h"

#define LENGTH 10
//256

static const char base64chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                   'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                   'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

void KAT_Blake2(uint8_t *input, uint8_t *hash)
{
    int i, j;
    printf("Running Blake2 :)\n\n");

    for (i = 0; i < LENGTH; ++i)
    {
        // printf("NEW WORD\n");
        // for (j = 0; j < i; ++j) {
        //     printf("Input Index %i is - %i\n", j, input[j]);
        // }
        blake2b(hash, BLAKE2B_OUTBYTES, input, i, NULL, 0);
        printf("\t{\n\t\t");

        for (j = 0; j < BLAKE2B_OUTBYTES - 3; j += 3)
        {
            // Encode the first character
            printf("%c", base64chars[hash[j] >> 2]);
            // Encode the second character
            printf("%c", base64chars[((hash[j] & 0x03) << 4) | ((hash[j + 1] & 0xf0) >> 4)]);
            // Encode the third character
            printf("%c", base64chars[((hash[j + 1] & 0x0f) << 2) | ((hash[j + 2] & 0xc0) >> 6)]);
            // Encode the fourth character
            printf("%c", base64chars[hash[j + 2] & 0x3f]);

            // printf("\tAdded indexes %i to %i\n", j, j + 2);
        }
        if (j >= 63) {
            printf("%c", base64chars[hash[j] >> 2]);
            printf("%c", base64chars[(hash[j] & 0x03) << 4]);
            printf("=");
            printf("=");
        }

        printf("\n\t},\n");
    }

    printf("};\n\n\n\n\n");

    return;
}


void KAT_Blake2_Keyed (uint8_t* key, uint8_t* input, uint8_t* hash) {
    int i, j;
    printf("Running Keyed Blake2 :)");

    for (i = 0; i < LENGTH; ++i)
    {
        blake2b(hash, BLAKE2B_OUTBYTES, input, i, key, BLAKE2B_KEYBYTES);
        printf("\t{\n\t\t");

        for (j = 0; j < BLAKE2B_OUTBYTES; j += 3)
        {
            // Encode the first character
            printf("%c", base64chars[hash[j] >> 2]);
            // Encode the second character
            printf("%c", base64chars[((hash[j] & 0x03) << 4) | ((hash[j + 1] & 0xf0) >> 4)]);
            // Encode the third character
            printf("%c", base64chars[((hash[j + 1] & 0x0f) << 2) | ((hash[j + 2] & 0xc0) >> 6)]);
            // Encode the fourth character
            printf("%c", base64chars[hash[j + 2] & 0x3f]);
        }

        // Print padding if necessary
        if (i < LENGTH - 1 || (BLAKE2B_OUTBYTES % 3) != 0)
        {
            int padding = ((BLAKE2B_OUTBYTES % 3) == 1) ? 2 : (((BLAKE2B_OUTBYTES % 3) == 2) ? 1 : 0);
            for (int p = 0; p < padding; p++)
            {
                printf("=");
            }
        }

        printf("\n\t},\n");
    }

    printf("};\n\n\n\n\n");

    return;
}

int main() {
    uint8_t key[64] = {0};
    uint8_t input[LENGTH] = {0};
    uint8_t hash[LENGTH] = {0};
    size_t i;

    for (i = 0; i < sizeof(input); ++i)
      input[i] = i;

    for (i = 0; i < sizeof(key); ++i)
      key[i] = 1;

    KAT_Blake2(input, hash);
    KAT_Blake2_Keyed(key, input, hash);

    return 0;
}
