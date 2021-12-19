#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    char *result = NULL;
    int i = 0;

    if (size < 0) {
        return NULL;
    }
    result = (char *)malloc((size + 1) * sizeof(char));
    
    while (i < size) {
        result[i] = '\0';
        i++;
    }
    result[i] = '\0';
    return result;
}

