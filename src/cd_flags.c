#include "../inc/ush.h"

void init_cd_flags(t_flags_cd *own_data) {

    own_data->flag_s = 0;
    own_data->flag_P = 0;

}

int cd_flags_setter(t_flags_cd *data_own, char **flags) {

    if (flags[1] != NULL) {

        if (flags[1][0] == '-') {

            for (int i = 1; i < mx_strlen(flags[1]); i++) {

                if (flags[1][i] == 'P') {
                    data_own->flag_P = 1;
                }
                else if (flags[1][i] == 's') {
                    data_own->flag_s = 1;
                }
                else {
                    mx_printerr("ush: cd: -");
                    char c = flags[1][i];
                    mx_printerr(&c);
                    mx_printerr(": invalid option\n");
                    mx_printerr("cd: usage: cd [-sP]\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}
