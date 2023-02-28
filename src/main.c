#include <stdio.h>
#include <string.h>

#include "util.h"

#include "subcmd/index.h"

// int SUBCMD_ENCRYPT = 0;
// int SUBCMD_DECRYPT = 1;
// int SUBCMD_SCRYPT = 2;
// int SUBCMD_SCRYPTPASS = 3;
// int SUBCMD_BASE64ENCODE = 4;
// int SUBCMD_BASE64DECODE = 5;

enum Subcmd{
    s_encrypt = 1,
    s_decrypt,
    s_scrypt,
    s_scryptpass,

    s_base64encode,
    s_base64decode
};

int main1(int argc, char const *argv[]) {
    if (argc == 0) {
        // Print help
        return 1;
    }

    int subcmd_code = atoi(argv[1]);

    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
    }

    switch(subcmd_code) {
        case s_encrypt:       subcmd_encrypt(argc, argv); break;
        case s_decrypt:       subcmd_decrypt(argc, argv); break;
        case s_scrypt:        subcmd_decrypt(argc, argv); break;
        case s_base64encode:  subcmd_decrypt(argc, argv); break;
        case s_base64decode:  subcmd_decrypt(argc, argv); break;
        default:
            printf("Unknown subcommand code: %d", subcmd_code);
            return 1;
    }

    return 0;
}

#define subcmd_is( cmd ) (strcmp(ARGV1, cmd) == 0 )

#include<stdio.h>
int main(int argc, char const *argv[])
{
    if (argc == 0) {
        // Print help
        return 1;
    }

    const char* ARGV1 = argv[1];

    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
        return 1;
    }

    if      ( 1 == subcmd_is("encrypt") )       subcmd_encrypt(argc, argv);
    else if ( 1 == subcmd_is("decrypt") )       subcmd_decrypt(argc, argv);
    else if ( 1 == subcmd_is("scrypt") )        subcmd_scrypt(argc, argv);
    else if ( 1 == subcmd_is("scryptpass") )    subcmd_scryptpass(argc, argv);
    else if ( 1 == subcmd_is("base64encode") )  subcmd_base64encode(argc, argv);
    else if ( 1 == subcmd_is("base64decode") )  subcmd_base64decode(argc, argv);
    else if ( 1 == subcmd_is("aead_xchacha20poly1305_encrypt") )
                                                subcmd_aead_xchacha20poly1305_encrypt(argc, argv);
    else if ( 1 == subcmd_is("aead_xchacha20poly1305_decrypt") )
                                                subcmd_aead_xchacha20poly1305_decrypt(argc, argv);
    else if ( 1 == subcmd_is("sealedbox_encrypt") )
                                                subcmd_sealedbox_encrypt(argc, argv);
    else if ( 1 == subcmd_is("sealedbox_decrypt") )
                                                subcmd_sealedbox_decrypt(argc, argv);
    else {
        return 1;
    }

    return 0;
}




