#include "../inc/libmx.h"

int mx_strlen(const char* s) {
    if (!s) {
        return 0;
    }

    int length = 0;

    while (s[length]) {
        length++;
    }

    return length;
}

