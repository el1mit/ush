#include "../inc/ush.h"

void read_command(char **l) {

    *l = mx_strnew(PATH_MAX);

    int r = get_input(l, PATH_MAX);
    
    replace_tilda_own(l);
    
    if (r == 0) {
        return;
    }

}

