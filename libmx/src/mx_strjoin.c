#include "../inc/libmx.h"

char* mx_strjoin(const char* s1, const char* s2) {
    if (!s1 && !s2) {
        return NULL;
    }
    else if (!s1) {
        return mx_strdup(s2);
    }
    else if (!s2) {
        return mx_strdup(s1);
    }
    else {
        int s1_len = mx_strlen(s1), s2_len = mx_strlen(s2);
        char* result = mx_strnew(s1_len + s2_len);

        result = mx_strcpy(result, s1);
        result = mx_strcat(result, s2);
        return result;
    }
}

