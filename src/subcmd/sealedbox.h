#include <stdlib.h>
#include <string.h>
#include <sodium.h>
#include <stdio.h>

#include "../util.h"

// ./main.o sealedbox_encrypt hi b7KAEVtR5MvuV5dJilUJigeZOvSI0VNUefFPDjVvLhs
int subcmd_sealedbox_encrypt( int argc, const char* argv[] ){
    // Convert key from hex string to binary

    // public key
    const char* msg = argv[2];
    unsigned long long mlen = strlen(msg);

    struct binary_data publickey = base64decode(argv[3]);

    unsigned char ciphertext[ crypto_box_SEALBYTES + mlen ];
    size_t ciphertext_len = crypto_box_SEALBYTES + mlen;

    if (crypto_box_seal(ciphertext, (const unsigned char *)msg, mlen, publickey.data) != 0){
        printf("Encryption failed\n");
    }

    struct binary_data aaa = { .len = ciphertext_len, .data = ciphertext };
    printf("cipher: %s\n", base64encode(aaa));

    return 0;
}

// ./main.o sealedbox_decrypt XVy5jK5CVFnnhuX8cPBFMPtdbCNFNh2hNBPHsDiMEUIN7vVuaguGqY2wAbeziQAriMw=  b7KAEVtR5MvuV5dJilUJigeZOvSI0VNUefFPDjVvLhs I25HCqHxo/ND9c2O0mIJIZgGq+SqbyVnYHqKwDgZQSc=
int subcmd_sealedbox_decrypt( int argc, const char* argv[] ){
    struct binary_data cipherdata = base64decode(argv[2]);

    struct binary_data publickey = base64decode(argv[3]);
    struct binary_data privatekey = base64decode(argv[4]);

    unsigned char msg[ cipherdata.len - crypto_box_SEALBYTES + 1 ];
    if (0 != crypto_box_seal_open(
        msg, cipherdata.data,
        cipherdata.len,
        publickey.data, privatekey.data
    )){
        printf("Decryption failed\n");
    }

    msg[ cipherdata.len - crypto_box_SEALBYTES ] = 0;
    printf("%s", (char*) msg);
    return 0;
}

