#include <string.h>
#include <sodium.h>
#include "../util.h"

/*
sodium_base64_VARIANT_ORIGINAL_NO_PADDING
sodium_base64_VARIANT_URLSAFE
sodium_base64_VARIANT_URLSAFE_NO_PADDING
*/

int subcmd_base64encode(int argc, char const *argv[]){
    const char* text = argv[2];

    printf("%s\n", base64encode((struct binary_data){strlen(text), (const unsigned char*)text}));
    return 0;
}

int subcmd_base64decode(int argc, char const *argv[]){
    struct binary_data res = base64decode(argv[2]);

    printf("%s\n", res.data);
    return 0;
}
