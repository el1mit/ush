#include "../inc/ush.h"

int unset_check_parameters_own(char **data_own) {

    for (int i = 1; data_own[i] != NULL; i++) {
    
        for (int j = 0; j < mx_strlen(data_own[i]); j++) {
        
            if ( mx_isspace(data_own[i][j]) 
            || data_own[i][j] == '=' || data_own[i][j] == '-'
            || data_own[i][j] == '.' || data_own[i][j] == ','
            || data_own[i][j] == '(' || data_own[i][j] == ']'
            || data_own[i][j] == ')' || data_own[i][j] == '*'
            || data_own[i][j] == '^' || data_own[i][j] == '%'
            || data_own[i][j] == '#' || data_own[i][j] == '@'
            || data_own[i][j] == '!' || data_own[i][j] == '+') {
                mx_printerr("ush: unset: '");
                mx_printerr(data_own[i]);
                mx_printerr("': not a valid identifier\n");

                return -1;

            }
            
        }
        
    }

    return 0;
}

int unset_own(const char *arr) {

    return unsetenv(arr);

}

