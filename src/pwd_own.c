#include "../inc/ush.h"

int pwd_own(t_flags_pwd *flags) {

    char *result = (char *)malloc(INT_MAX);

    if (flags->flag_L) {
        result = mx_strdup(t_global.PWD);
    }
    else {
        getcwd(result, INT_MAX);
    }
    
    mx_printstr(result);
    mx_printstr("\n");
    
    free(result);
    return 0;
}
