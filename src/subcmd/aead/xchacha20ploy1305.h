#include <stdlib.h>
#include <sodium.h>
#include <stdio.h>
#include <string.h>

#include "../../util.h"

int subcmd_aead_xchacha20poly1305_encrypt( int argc, const char* argv[] ){
    // Convert key from hex string to binary

    unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];
    memset(key, 0, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
    size_t keylen;
    if (sodium_hex2bin(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES, argv[2], strlen(argv[2]), NULL, &keylen, NULL) != 0) {
        printf("Invalid key\n");
        return 1;
    }

    struct binary_data ttt = { .len = keylen, .data = key };
    printf("encrypted key: %zu, %s %s\n", keylen, argv[2], base64encode(ttt));

    // Convert nonce from hex string to binary
    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];
    memset(nonce, 0, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
    if (sodium_hex2bin(nonce, sizeof nonce, argv[3], strlen(argv[3]), NULL, NULL, NULL) != 0) {
        printf("Invalid nonce\n");
        return 1;
    }

    const char * plaintext = argv[4];

    // Encrypt
    unsigned long long ciphertext_len;
    unsigned char ciphertext[1024];
    // unsigned char mac[crypto_aead_xchacha20poly1305_ietf_ABYTES];
    if (crypto_aead_xchacha20poly1305_ietf_encrypt(ciphertext, &ciphertext_len,
                                                   (const unsigned char *)plaintext, strlen(plaintext),
                                                   NULL, 0,
                                                   NULL,
                                                   nonce, key) != 0) {
        printf("Encryption failed\n");
        return 1;
    }

    struct binary_data aaa = { .len = ciphertext_len, .data = ciphertext };
    printf("cipher: %s\n", base64encode(aaa));

    printf("%llu\n", ciphertext_len);

    return 0;
}

int subcmd_aead_xchacha20poly1305_encrypt_detach( int argc, char* argv[]){
    return 0;
}


// ./main.o aead_xchacha20poly1305_encrypt 1AAA 1A abccdaef
// ./main.o aead_xchacha20poly1305_decrypt 1AAA 1A M8aii9oa6zXBOr/wJ9kFR0+185YPWhZyVKZNRgI=
int subcmd_aead_xchacha20poly1305_decrypt( int argc, const char* argv[] ){
    // Convert key from hex string to binary
    unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];
    memset(key, 0, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
    size_t keylen;
    if (sodium_hex2bin(key, sizeof key, "1AAA", 4, NULL, &keylen, NULL) != 0) {
        printf("Invalid key\n");
        return 1;
    }

    struct binary_data aaa = { .len = keylen, .data = key };
    printf("decrypt key: %zu, %s %s\n", keylen, argv[2], base64encode(aaa));

    // Convert nonce from hex string to binary
    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];
    memset(nonce, 0, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
    if (sodium_hex2bin(nonce, sizeof nonce, argv[3], strlen(argv[3]), NULL, NULL, NULL) != 0) {
        printf("Invalid nonce\n");
        return 1;
    }

    struct binary_data binarystr = base64decode(argv[4]);

    printf("len: %s\n", argv[4]);
    printf("len: %zu\n", binarystr.len);

    // Decrypt
    unsigned long long plaintext_len;
    unsigned char plaintext[1024];
    if (crypto_aead_xchacha20poly1305_ietf_decrypt(plaintext, &plaintext_len,
                                                   NULL,
                                                   binarystr.data, binarystr.len,
                                                   NULL, 0,
                                                   nonce, key) != 0) {
        printf("Decryption failed\n");
        return 1;
    }

    printf("%s\n", plaintext);


    return 0;
}

