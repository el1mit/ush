#include "../inc/ush.h"

void init_which_flags(t_flags_which *data_own) {

    data_own->flag_A = 0;
    data_own->flag_S = 0;

}

int which_flags_setter(t_flags_which *data_own, char **flags) {

    if (flags[1] != NULL) {

        if (flags[1][0] == '-') {

            for (int i = 1; i < mx_strlen(flags[1]); i++) {

                if (flags[1][i] == 'a') {
                    data_own->flag_A = 1;
                }
                else if (flags[1][i] == 's') {
                    data_own->flag_S = 1;
                }
                else {
                    mx_printerr("which: bad option: -");
                    char c = flags[1][i];
                    mx_printerr(&c);
                    mx_printerr("\n");
                    return 1;
                }

            }
        }
    }

    return 0;
}


