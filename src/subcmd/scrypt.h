#include <string.h>
#include <sodium.h>

#define KEY_LEN crypto_box_SEEDBYTES

// Refer: https://doc.libsodium.org/advanced/scrypt
int scrypt( const char* password ){

    unsigned char salt[crypto_pwhash_scryptsalsa208sha256_SALTBYTES];
    unsigned char key[KEY_LEN];

    randombytes_buf(salt, sizeof salt);

    if (crypto_pwhash_scryptsalsa208sha256
        (key, sizeof key, password, strlen(password), salt,
            crypto_pwhash_scryptsalsa208sha256_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_scryptsalsa208sha256_MEMLIMIT_INTERACTIVE) != 0) {
        /* out of memory */
    }

    char cipher[2048];  // how to find out the length of the cipher
    sodium_bin2hex(cipher, sizeof cipher, key, sizeof key);

    printf("key: %s\n", cipher);
    return 1;
}

int scrypt_cmp( const char* pass, const char* hashpass ){
    if (crypto_pwhash_scryptsalsa208sha256_str_verify(hashpass, pass, strlen(pass)) != 0) {
        /* incorrect password */
        return 0;
    } else {
        return 1;
    }
}

int scrypt_gen( const char* pass ){
    char hashpass[crypto_pwhash_scryptsalsa208sha256_STRBYTES];
    if (crypto_pwhash_scryptsalsa208sha256_str(
        hashpass, pass, strlen(pass),
        crypto_pwhash_scryptsalsa208sha256_OPSLIMIT_SENSITIVE,
        crypto_pwhash_scryptsalsa208sha256_MEMLIMIT_SENSITIVE) != 0) {

        return 1;
    }

    printf("%s\n", hashpass);

    printf("cmp: %d\n", scrypt_cmp(pass, hashpass));
    return 0;
}


int subcmd_scrypt(int argc, char const *argv[]){
    scrypt(argv[2]);
    return 0;
}

int subcmd_scryptpass(int argc, char const *argv[]){
    scrypt_gen(argv[2]);
    return 0;
}



