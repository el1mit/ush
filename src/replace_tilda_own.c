#include "../inc/ush.h"

static void to_parent(char** arr) {

    char* ptr = strrchr(*arr, '/');

    if (ptr) {
        mx_memset(ptr + 1, '\0', mx_strlen(ptr));
    }
    else {
        (*arr)[0] = '/';
    }

}

void replace_tilda_own(char **str) {

    char *tmp = NULL;
    int ind = -1;

    int pwd_len = mx_strlen(t_global.PWD);
    int oldpwd_len = mx_strlen(t_global.OLDPWD);
    int home_len = mx_strlen(t_global.HOME);

    while (true) {

        ind = mx_get_substr_index(*str, "~+/");

        if (ind == -1) {
            break;
        }

        tmp = malloc(PATH_MAX);
        mx_memset(tmp, 0, PATH_MAX);
        mx_memcpy(tmp, *str, ind);
        mx_memcpy(tmp + ind, t_global.PWD, pwd_len);

        if (tmp[ind + pwd_len - 1] == '/' && (*str)[ind + 2] == '/') {

            tmp[ind + pwd_len - 1] = '\0';
            pwd_len--;

        }

        mx_memcpy(tmp + ind + pwd_len,
            *str + ind + 2, PATH_MAX - ind - 2 - pwd_len);

        free(*str);
        *str = mx_strdup(tmp);
        free(tmp);
        tmp = NULL;

    }

    while (true) {

        ind = mx_get_substr_index(*str, "~-/");

        if (ind == -1) {
            break;
        }

        tmp = malloc(PATH_MAX);
        mx_memset(tmp, 0, PATH_MAX);
        mx_memcpy(tmp, *str, ind);
        mx_memcpy(tmp + ind, t_global.OLDPWD, oldpwd_len);

        mx_memcpy(tmp + ind + oldpwd_len,
            *str + ind + 2, PATH_MAX - ind - 2 - oldpwd_len);

        free(*str);
        *str = mx_strdup(tmp);
        free(tmp);
        tmp = NULL;

    }

    while (true) {

        ind = mx_get_substr_index(*str, "~/");

        if (ind == -1) {
            break;
        }

        tmp = malloc(PATH_MAX);
        mx_memset(tmp, 0, PATH_MAX);
        mx_memcpy(tmp, *str, ind);
        mx_memcpy(tmp + ind, t_global.HOME, home_len);

        mx_memcpy(tmp + ind + home_len,
            *str + ind + 1, PATH_MAX - ind - 1 - home_len);

        free(*str);
        *str = mx_strdup(tmp);
        free(tmp);
        tmp = NULL;
    }

    while (true) {

        ind = mx_get_char_index(*str, '~');
        char *ptr = mx_strchr(*str, '~');

        if (ind == -1 || (*str)[ind + 1] == ' ' || (*str)[ind + 1] == '\0' || !mx_isalpha(*(ptr + 1))) {
            break;
        }

        tmp = malloc(PATH_MAX);
        mx_memset(tmp, 0, PATH_MAX);
        mx_memcpy(tmp, *str, ind);
        mx_memcpy(tmp + ind, t_global.HOME, home_len);

        to_parent(&tmp);

        mx_memcpy(tmp + mx_strlen(tmp), 
            *str + ind + 1, PATH_MAX - ind - 1 - home_len);

        free(*str);
        *str = mx_strdup(tmp);
        free(tmp);
        tmp = NULL;

    }

    while (true) {

        ind = mx_get_char_index(*str, '~');

        if (ind == -1) {
            break;
        }

        tmp = malloc(PATH_MAX);
        mx_memset(tmp, 0, PATH_MAX);
        mx_memcpy(tmp, *str, ind);
        mx_memcpy(tmp + ind, t_global.HOME, home_len);

        mx_memcpy(tmp + ind + home_len,
            *str + ind + 1, PATH_MAX - ind - 1 - home_len);

        free(*str);
        *str = mx_strdup(tmp);
        free(tmp);
        tmp = NULL;

    }
}


