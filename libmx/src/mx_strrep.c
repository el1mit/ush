#include "../inc/libmx.h"

char *mx_strrep(char *s1, char *s2, char *r) {

    char *out = malloc(PATH_MAX);
    mx_memset(out, 0, PATH_MAX);
    int i = 0, j = 0, flag = 0, start = 0;

    while (s1[i] != '\0')
    {
            if (s1[i] == s2[j])
            {
                if (!flag) {
                    start = i;
                }

                
                j++;
                
                if (s2[j] == '\0') {
                    break;
                }
                
                flag = 1;
            } 
            else 
            {
                    flag = start = j = 0;
            }
            i++;
    }

    if (s2[j] == '\0' && flag)
    {
        for (i = 0; i < start; i++) {
            out[i] = s1[i];
        }
 
        for (j = 0; j < mx_strlen(r); j++)
        {

            out[i] = r[j];
            i++;

        }
            
        for (j = start + mx_strlen(s2); j < mx_strlen(s1); j++)
        {
            out[i] = s1[j];
            i++;
        }
            
        out[i] = '\0';

        return out;

    } else {

        free(out);

        return NULL;

    }
}

