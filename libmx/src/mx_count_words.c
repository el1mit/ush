#include "../inc/libmx.h"

int mx_count_words(const char* str, char c) {
    if (!str) {
        return -1;
    }
    
    bool start_count = true;
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            start_count = true;
        }
        else if (start_count == true) {
            start_count = false;
            count++;
        }
    }

    return count;
}

