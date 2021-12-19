#include "../inc/libmx.h"

char** mx_strsplit(const char* s, char c) {
    if (!s) {
        return NULL;
    }

    int word_len = 0;
    int i = 0;

    char** arr = NULL;
    arr = (char**)malloc((mx_count_words(s, c) + 1) * sizeof(char*));
   
    while ((*s) && (*s != '\0')) {
        word_len = 0;
        if (*s != c) {

            const char* temp = s;
            while (temp[word_len] && temp[word_len] != c) {
                word_len++;
            }

            arr[i] = mx_strndup(s, word_len);
            s += word_len;
            i++;
            continue;
        }
        s++;
    }
    arr[i] = NULL;
    return arr;
}

