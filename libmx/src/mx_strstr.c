#include "../inc/libmx.h"

char* mx_strstr(const char* haystack, const char* needle) {
    int haystack_len = mx_strlen(haystack);
    int needle_len = mx_strlen(needle);

    for (int i = 0; i < haystack_len; haystack++, i++) {
        char* temp = mx_strchr(haystack, haystack[0]);

        if (mx_strncmp(temp, needle, needle_len) == 0) {
            return (char*)haystack;
        }
    }
    return NULL;
}

