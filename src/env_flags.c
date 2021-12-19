#include "../inc/ush.h"

void init_env_flags(t_flags_env *data_own) {

    data_own->flag_I = 0;
    data_own->flag_U = 0;
    data_own->flag_P = 0;

}


int env_flags_setter(t_flags_env *data_own, char **parameters) {

    if (parameters[1] != NULL) {

        if (parameters[1][0] == '-') {

            for (int i = 1; i < mx_strlen(parameters[1]); i++) {

                if (parameters[1][i] == 'P') {
                    data_own->flag_P = 1;
                    data_own->flag_I = 0;
                    data_own->flag_U = 0;
                }
                else if (parameters[1][i] == 'i') {
                    data_own->flag_I = 1;
                    data_own->flag_U = 0;
                    data_own->flag_P = 0;
                }
                else if (parameters[1][i] == 'u') {
                    data_own->flag_U = 1;
                    data_own->flag_I = 0;
                    data_own->flag_P = 0;
                }
                else {
                    mx_printerr("env: invalid option -- '");
                    char c = parameters[1][i];
                    mx_printerr(&c);
                    mx_printerr("'\nTry 'env --help' for more information.\n");
                    return 1;
                }

            }
        }
    }

    return 0;
}
