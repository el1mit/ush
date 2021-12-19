#include "../inc/ush.h"

static void a_escapes(char** arr) {

    char* ptr = mx_strchr(*arr, '"');

    if (ptr != NULL) {

        char* sl_ptr = mx_strchr(ptr, '\\');

        while (sl_ptr != NULL) {
            switch (*(sl_ptr + 1))
            {
            case 'n':
                *sl_ptr = '\n';
                break;
            case 't':
                *sl_ptr = '\t';
                break;
            case '\\':
                *sl_ptr = '\\';
                break;
            case 'a':
                *sl_ptr = '\a';
                break;
            case 'v':
                *sl_ptr = '\v';
                break;
            case 'b':
                *sl_ptr = '\b';
                break;
            case 'f':
                *sl_ptr = '\f';
                break;
            case 'r':
                *sl_ptr = '\r';
                break;
            default:
                break;
            }

            sl_ptr++;
            *sl_ptr = '\0';

            for (; *(sl_ptr + 1) != '\0';) {

                mx_swap_char(sl_ptr, sl_ptr + 1);
                sl_ptr++;

            }
            sl_ptr = ptr + 1;

            if (mx_get_char_index(sl_ptr, '\\') > mx_get_char_index(sl_ptr, '"') || mx_get_char_index(sl_ptr, '\\') == -1) {

                ptr = mx_strchr(sl_ptr, '\'');
                break;

            }

            sl_ptr = mx_strchr(ptr, '\\');
        }
    }
    else {
        ptr = mx_strchr(*arr, '\'');
    }

    if (ptr != NULL) {

        char* slash_ptr = mx_strchr(ptr, '\\');

        while (slash_ptr != NULL) {
            switch (*(slash_ptr + 1))
            {
            case 'n':
                *slash_ptr = '\n';
                break;
            case 't':
                *slash_ptr = '\t';
                break;
            case '\\':
                *slash_ptr = '\\';
                break;
            case 'a':
                *slash_ptr = '\a';
                break;
            case 'v':
                *slash_ptr = '\v';
                break;
            case 'b':
                *slash_ptr = '\b';
                break;
            case 'f':
                *slash_ptr = '\f';
                break;
            case 'r':
                *slash_ptr = '\r';
                break;
            default:
                break;
            }

            slash_ptr++;
            *slash_ptr = '\0';

            for (; *(slash_ptr + 1) != '\0';) {

                mx_swap_char(slash_ptr, slash_ptr + 1);
                slash_ptr++;

            }

            if (mx_get_char_index(slash_ptr, '\\') > mx_get_char_index(slash_ptr, '\'') || mx_get_char_index(slash_ptr, '\\') == -1) {
                break;
            }

            slash_ptr = mx_strchr(ptr, '\\');
        }
    }
}

static void delete_spaces(char** str) {

    if (strchr(*str, '"') || strchr(*str, '\'')) {
        return;
    }

    *str = mx_del_extra_spaces(*str);

}

int echo_own(t_flags_echo *flags, char **str) {

    delete_spaces(str);
    *str = mx_strtrim(*str);
    a_escapes(str);

    char **data_own = mx_strsplit(*str, '>');
    char *ptr = data_own[0];
    char *tmp_ptr = ptr;

    while (*tmp_ptr != '\0' && *tmp_ptr != ' ') {

        *tmp_ptr = '\0';

        for (; *(tmp_ptr + 1) != '\0';) {

            mx_swap_char(tmp_ptr, tmp_ptr + 1);
            tmp_ptr++;

        }

        tmp_ptr = ptr;
    }

    *tmp_ptr = '\0';

    for (; *(tmp_ptr + 1) != '\0';) {

        mx_swap_char(tmp_ptr, tmp_ptr + 1);
        tmp_ptr++;

    }

    tmp_ptr = ptr;

    if (*tmp_ptr == '-') {

        while (*tmp_ptr != '\0' && *tmp_ptr != ' ') {

            *tmp_ptr = '\0';

            for (; *(tmp_ptr + 1) != '\0';) {

                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;

            }

            tmp_ptr = ptr;
        }
    }

    if (*tmp_ptr == ' ') {

        *tmp_ptr = '\0';

        for (; *(tmp_ptr + 1) != '\0';) {

            mx_swap_char(tmp_ptr, tmp_ptr + 1);
            tmp_ptr++;

        }

        tmp_ptr = ptr;
    }

    tmp_ptr = ptr;

    if(flags->flag_N) {

        bool isWrite = true;
        char *str = NULL;
        str = mx_strnew(PATH_MAX);

        if(data_own[1] != NULL) {

            FILE *file;
            char *path = mx_strdup(getenv("PWD"));
            char *newpath = mx_strcat(path, "/");
            newpath = mx_strcat(newpath, data_own[1]);
            file = fopen(newpath, "w");                
            fprintf(file, "%s", ptr);
            fclose(file);
            free(path);
            isWrite = false;

        }
        else {

            mx_strcat(str, data_own[0]);

        }

        int count = 0;
        bool parants = false;

        for (int i = 0; str[i]; i++) {

            if (str[i] == '"' || str[i] == '\'') {

                for (int j = i; str[j]; j++) {
                    str[j] = str[j + 1];
                }

                count++;
                parants = true;

            }
            else if (str[i] == '\\') {

                if (!parants) {

                    for (int j = i; str[j]; j++) {
                        str[j] = str[j+1];
                    }

                }
            }
        }

        if(count % 2 == 0 || count == 0) {

            if(isWrite) {
                mx_printstr(str);
            }

        }
        else {

            mx_printerr("Odd number of quotes.\n");
            mx_del_strarr(&data_own);
            return 1;

        }
    }
    else if (flags->flag_e || flags->flag_E) {

        bool isWrite = true;
        char *str = NULL;
        str = mx_strnew(PATH_MAX);

        if(data_own[1] != NULL) {

            FILE *file;
            char *path = mx_strdup(getenv("PWD"));
            char *newpath = mx_strcat(path, "/");
            newpath = mx_strcat(newpath, data_own[1]);
            file = fopen(newpath, "w");                
            fprintf(file, "%s", ptr);
            fclose(file);
            free(path);
            isWrite = false;

        }
        else {
            mx_strcat(str, ptr);
        }

        int count = 0;
        bool parants = false;

        for (int i = 0; str[i]; i++) {

            if (str[i] == '"' || str[i] == '\'') {

                for (int j = i; str[j]; j++) {
                    str[j] = str[j + 1];
                }

                count++;
                parants = true;

            }
            else if (str[i] == '\\') {

                if (!parants) {
                    for (int j = i; str[j]; j++) {
                        str[j] = str[j+1];
                    }
                }

            }
        }

        if(count % 2 == 0 || count == 0) {

            if(isWrite) {
                mx_printstr(str);
                mx_printchar('\n');
            }
        }
        else {

            mx_printerr("Odd number of quotes.\n");
            mx_del_strarr(&data_own);
            return 1;
        }
    }
    else {

        bool isWrite = true;
        char *str = NULL;
        str = mx_strnew(PATH_MAX);

        if(data_own[1] != NULL) {

            FILE *file;
            char *path = mx_strdup(getenv("PWD"));
            char *newpath = mx_strcat(path, "/");
            newpath = mx_strcat(newpath, data_own[1]);
            file = fopen(newpath, "w");                
            fprintf(file, "%s", ptr);
            fclose(file);
            free(path);
            isWrite = false;

        }
        else {
            mx_strcat(str, ptr);
        }

        int count = 0;
        bool parants = false;

        for (int i = 0; str[i]; i++) {

            if (str[i] == '"' || str[i] == '\'') {

                for (int j = i; str[j]; j++) {
                    str[j] = str[j + 1];
                }

                count++;
                parants = true;

            }
            else if (str[i] == '\\') {

                if (!parants) {

                    for (int j = i; str[j]; j++) {
                        str[j] = str[j+1];
                    }
                }
            }
        }

        if(count % 2 == 0 || count == 0) { 

            if (isWrite) {

                mx_printstr(str);
                mx_printchar('\n');
            }
        }
        else {

            mx_printerr("Odd number of quotes.\n");
            mx_del_strarr(&data_own);
            return 1;
        }
    }

    mx_del_strarr(&data_own);
    return 0;
}

