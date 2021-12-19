#include "../inc/libmx.h"

char* mx_del_extra_spaces(const char* str) {
    char* temp = NULL;
    char* result = NULL;

    if (!str) {
        return NULL;
    }

    temp = mx_strnew(mx_strlen(str));

    for (int i = 0, j = 0; str[i]; i++) {
        if (!(mx_isspace(str[i]))) {
            temp[j] = str[i];
            j++;
        }
        if (!(mx_isspace(str[i])) && mx_isspace(str[i + 1])) {
            temp[j] = ' ';
            j++;
        }
    }
    result = mx_strtrim(temp);
    mx_strdel(&temp);
    return result;
}

