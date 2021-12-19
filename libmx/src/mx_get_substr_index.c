#include "../inc/libmx.h"

int mx_get_substr_index(const char* str, const char* sub) {
    int i = 0;
    int sub_len = 0;

    if (sub && str) {
        sub_len = mx_strlen(sub);
        
        while (*str) {
            if (mx_strncmp(str, sub, sub_len) == 0) {
                return i;
            }
            i++;
            str++;
        }
        return -1;
    }
    return -2;
}

