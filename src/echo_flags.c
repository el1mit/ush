#include "../inc/ush.h"

void init_echo_flags(t_flags_echo *data_own) {

    data_own->flag_N = 0;
    data_own->flag_e = 0;
    data_own->flag_E = 0;

}

int echo_flags_setter(t_flags_echo *data_own, char **flags) {

    if (flags[1] != NULL) {

        if (flags[1][0] == '-') {

            for (int i = 1; i < mx_strlen(flags[1]); i++) {

                if (flags[1][i] == 'n') {
                    data_own->flag_N = 1;
                }
                else if (flags[1][i] == 'e') {
                    data_own->flag_e = 1;
                    data_own->flag_E = 0;
                }
                else if (flags[1][i] == 'E') {
                    data_own->flag_E = 1;
                    data_own->flag_e = 0;
                }
                else {
                    return 1;
                }
                
            }
        }
    }

    return 0;
}
