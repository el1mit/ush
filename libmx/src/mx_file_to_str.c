#include "../inc/libmx.h"

char* mx_file_to_str(const char* file) {
    int fl = open(file, O_RDONLY);
    int file_size = 0;

    if (fl < 0) {
        close(fl);
        return NULL;
    }
    char buffer;
    int count_len = read(fl, &buffer, 1);
    while (count_len > 0) {
        count_len = read(fl, &buffer, 1);
        file_size++;
    }
    close(fl);

    fl = open(file, O_RDONLY);
    if (fl == -1) {
        close(fl);
        return NULL;
    }
    if (file_size == 0) {
        return NULL;
    }

    char* result = mx_strnew(file_size);
    read(fl, result, file_size);
    close(fl);
    return result;
}

