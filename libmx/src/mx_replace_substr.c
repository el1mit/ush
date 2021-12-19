#include "../inc/libmx.h"

char* mx_replace_substr(char *str, char *sub, char *replace) {

    int i = mx_get_substr_index(str, sub);

    if (i == -1) {
        return NULL;
    }

    int nlen = mx_strlen(replace);
    int len = mx_strlen(str) + mx_strlen(replace);
    char *result = mx_strnew(len);
    mx_memcpy(result, str, i);

    if (nlen > 0) {
        mx_memcpy(result + i, replace, nlen);
    }

    mx_memcpy(result + i + nlen, str + i + mx_strlen(sub), len - i - mx_strlen(sub) - nlen);
    free(str);

    return result;
}

