#include "../inc/ush.h"

void escape_sequences(char ***arr) {

    char **data = *arr;

    for (int i = 0; data[i] != NULL; i++) {

        int len = mx_strlen(data[i]);

        if (data[i][len - 1] == '\\') {

            data[i][len - 1] = ' ';
            data[i] = mx_strjoin(data[i], data[i + 1]);
            free(data[i + 1]);
            data[i + 1] = NULL;

            for (int j = i + 1; data[j + 1] != NULL; j++) {

                char *tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;

            }

            i--;
        }
    }

    for (int i = 0; data[i] != NULL; i++) {

        char *esc = mx_strchr(data[i], '\\');

        while (esc != NULL) {

            switch (*(esc + 1))
            {
            case 'n':
                *esc = '\n';
                break;
            case 't':
                *esc = '\t';
                break;
            case '\\':
                *esc = '\\';
                break;
            case '\'':
                *esc = '\'';
                break;
            case '"':
                *esc = '\"';
                break;
            case '`':
                *esc = '`';
                break;
            case 'a':
                *esc = '\a';
                break;
            default:
                break;
            }
            
            esc++;
            *esc = '\0';

            for (; *(esc + 1) != '\0';) {

                mx_swap_char(esc, esc + 1);
                esc++;

            }

            esc = mx_strchr(data[i], '\\');
        }

    }
}


