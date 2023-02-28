#include <string.h>

#include <sodium.h>
#include "util.h"

char* base64encode( struct binary_data bin ){
    // const int textlen = strlen((const char* )text);

    int BASE64_LENGTH = sodium_base64_ENCODED_LEN(bin.len, sodium_base64_VARIANT_ORIGINAL);
    char *b64 = malloc(BASE64_LENGTH * sizeof(char));

    sodium_bin2base64(
        b64, BASE64_LENGTH,
        bin.data, bin.len,
        sodium_base64_VARIANT_ORIGINAL
    );
    return b64;
}

struct binary_data base64decode( const char* text ){
    const int textlen = strlen(text);

    size_t bin_len;

    int BIN_LENGTH = strlen(text);
    unsigned char *bin = malloc(2 * BIN_LENGTH * sizeof(char));

    sodium_base642bin(bin, 2 * BIN_LENGTH,
                      text, textlen, "", &bin_len, NULL,
                      sodium_base64_VARIANT_ORIGINAL);

    // bin[bin_len] = 0;
    struct binary_data res = {
        bin_len,
        bin
    };

    return res;
}
