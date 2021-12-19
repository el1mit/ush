#include "../inc/ush.h"

int get_input(char **arr, int len) {

    int input = read(0, *arr, len);

    if (!input) {

        size_t n = len - 5;
        input = getline(arr, &n, 0);

    }

    (*arr)[input - 1] = '\0';
    input = input - 1;

    return input;
}
