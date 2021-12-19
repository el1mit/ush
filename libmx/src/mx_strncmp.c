#include "../inc/libmx.h"

int mx_strncmp(const char* s1, const char* s2, int count) {
    while (count) {
        if (*s1 != *s2) {
            return *(const unsigned char*)s1 - *(const unsigned char*)s2;
        }

        s1++;
        s2++;
        count--;
    }
    return 0;
}

