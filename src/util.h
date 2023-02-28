#pragma once

struct binary_data {
    size_t len;
    const unsigned char* data;
};

char* base64encode( struct binary_data bin );
struct binary_data base64decode(const char* text);
