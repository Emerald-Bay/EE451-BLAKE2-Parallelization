#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blake2.h"

#define STR_(x) #x
#define STR(x) STR_(x)

#define LENGTH 256

void KAT_Blake2 (uint8_t* input, uint8_t* hash) {
    int i, j;
    printf("Running Blake2 :)");

    for (i = 0; i < LENGTH; ++i) {
      blake2b(hash, BLAKE2B_OUTBYTES, input, i, NULL, 0);
      printf("\t{\n\t\t");

      for (j = 0; j < BLAKE2B_OUTBYTES; ++j) {
        if ((j + 1) == BLAKE2B_OUTBYTES) {
          printf("0x%02X%s", hash[j], "\n");
        }
        else {
          if (!((j + 1) % 8)) {
            printf("0x%02X%s", hash[j], ",\n\t\t");
          }
          else {
            printf("0x%02X%s", hash[j], ", ");
          }
        }
      }

      printf("\t},\n");
    }
    
    printf("};\n\n\n\n\n");

    return;
}

void KAT_Blake2_Keyed (uint8_t* key, uint8_t* input, uint8_t* hash) {
    int i, j;
    printf("Running Keyed Blake2 :)");

    for (i = 0; i < LENGTH; ++i) {
      blake2b(hash, BLAKE2B_OUTBYTES, input, i, key, BLAKE2B_KEYBYTES);
      printf("\t{\n\t\t");

      for (j = 0; j < BLAKE2B_OUTBYTES; ++j) {
        if ((j + 1) == BLAKE2B_OUTBYTES) {
          printf("0x%02X%s", hash[j], "\n");
        }
        else {
          if (!((j + 1) % 8)) {
            printf("0x%02X%s", hash[j], ",\n\t\t");
          }
          else {
            printf("0x%02X%s", hash[j], ", ");
          }
        }
      }

      printf("\t},\n");
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
      key[i] = i;

    KAT_Blake2(input, hash);
    KAT_Blake2_Keyed(key, input, hash);

    return 0;
}
