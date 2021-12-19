#include "../inc/ush.h"

void init_pwd_flags(t_flags_pwd *data_own) {

    data_own->flag_L = 1;
    data_own->flag_P = 0;

}

int pwd_flags_setter(t_flags_pwd *data_own, char **flags) {

    if (flags[1] != NULL) {

        if (flags[1][0] == '-') {

            for (int i = 1; i < mx_strlen(flags[1]); i++) {

                if (flags[1][i] == 'P') {
                    data_own->flag_P = 1;
                    data_own->flag_L = 0;
                }
                else if (flags[1][i] == 'L') {
                    data_own->flag_L = 1;
                    data_own->flag_P = 0;
                }
                else {
                    mx_printerr("ush: pwd: -");
                    char c = flags[1][i];
                    mx_printerr(&c);
                    mx_printerr(": invalid option\n");
                    mx_printerr("pwd: usage: pwd [-LP]\n");
                    return 1;
                }

            }
        }
    }

    return 0;
}
