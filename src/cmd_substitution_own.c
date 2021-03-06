#include "../inc/ush.h"

static char* exe_cmd_own(char* line_own) {

    char** arr = mx_strsplit(line_own, ' ');
    char* result = mx_strnew(PATH_MAX);
    char** own_path_dir = mx_strsplit(getenv("PATH"), ':');

    struct stat sb;

    for (int i = 0; own_path_dir[i] != NULL; i++) {

        char* cmd = NULL;

        if (arr[0][0] != '/') {

            cmd = mx_strdup(own_path_dir[i]);
            cmd = mx_strjoin(cmd, "/");
            cmd = mx_strjoin(cmd, arr[0]);

        }
        else {
            cmd = mx_strdup(arr[0]);
        }

        if (lstat(cmd, &sb) != -1) {

            result = mx_strjoin(result, cmd);
            free(cmd);
            result = mx_strjoin(result, line_own + mx_strlen(arr[0]));
            mx_del_strarr(&own_path_dir);

            return result;
        }

        if (cmd != NULL) {

            free(cmd);
            cmd = NULL;

        }
    }

    return result;
}

int cmd_substitution_own(char **str) {

    char *data = *str;

    char *ptr = mx_strchr(data, '`');

    if (ptr) {

        if (mx_count_substr(ptr, "`") % 2 != 0) {
            return 0;
        }

        while (ptr != NULL) {

            char *tmp_ptr = ptr;

            *ptr = '\0';

            for (; *(tmp_ptr + 1) != '\0';) {

                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;

            }

            tmp_ptr = ptr;
            char *var = mx_strnew(PATH_MAX);
            int j = 0;

            for (; *tmp_ptr != '`' && *tmp_ptr != '\0'; j++) {

                var[j] = *tmp_ptr;
                tmp_ptr++;

            }

            var[j] = '\0';
            *tmp_ptr = '\0';

            for (; *(tmp_ptr + 1) != '\0';) {

                mx_swap_char(tmp_ptr, tmp_ptr + 1);
                tmp_ptr++;

            }

            char *var2 = mx_strdup(var);

            for (char *tmp = var; *tmp != '\0' && *tmp != ' '; tmp++) {

                char c = *tmp;

                if (c < 97) {

                    c += 32;
                    *tmp = c;

                }

            }

            char **arr = mx_strsplit(var, ';');

            for (int i = 0; arr[i] != NULL; i++) {

                char *command = exe_cmd_own(var);
                FILE *fp;
                char *strreplace = mx_strnew(PATH_MAX);
                fp = popen(command, "r");

                if (fp == NULL) {

                    mx_printerr("Failed to run command\n");
                    return 1;

                }

                char *strrep_ptr = strreplace;

                while (fgets(strrep_ptr, PATH_MAX, fp) != NULL) {

                    strrep_ptr = strreplace + mx_strlen(strreplace);
                    strreplace[mx_strlen(strreplace) - 1] = ' ';

                }

                strreplace[mx_strlen(strreplace) - 1] = '\0';
                pclose(fp);
                
                *str = mx_strrep(*str, var2, strreplace);
                free(strreplace);
                free(command);

            }

            free(var2);
            mx_del_strarr(&arr);

            data = *str;
            free(var);
            ptr = mx_strchr(data, '`');

        }
    }
    
    ptr = strchr(data, '$');

    if (!ptr) {
        return 0;
    }

    while (ptr != NULL) {

        if (*(ptr + 1) == '{' || *(ptr + 1) == '(') {

            ptr = strchr(++ptr, '$');
            continue;

        }

        char *tmp_ptr = ptr;

        if (*(ptr + 1) != '(' && *(ptr + 1) != '{') {

            int ptr_len = mx_strlen(ptr) + 2;
            char *str_to_replace = mx_strnew(ptr_len);
            char *str_var = mx_strnew(ptr_len);

            str_to_replace[0] = *tmp_ptr;
            tmp_ptr++;

            for (int i = 1, j = 0; *tmp_ptr != '\0' && *tmp_ptr != ' ' && *tmp_ptr != '$'; i++, j++) {

                if (*tmp_ptr != '?') {

                    if (!mx_isalpha(*tmp_ptr)) {
                        break;
                    }
                }

                str_to_replace[i + 1] = '\0';
                str_var[j + 1] = '\0';

                str_to_replace[i] = *tmp_ptr;
                str_var[j] = *tmp_ptr;

                if (str_var[0] == '?') {
                    break;
                }

                tmp_ptr++;

            }

            if (str_var[0] == '?') {

                char *status = mx_itoa(t_global.exit_status);
                *str = mx_replace_substr(*str, str_to_replace, status);
                free(status);
                free(str_to_replace);
                free(str_var);
                ptr = strchr(*str, '$');

                continue;

            }
            
            char *env_val = getenv(str_var);
            char *env = NULL;

            if (env_val == NULL) {
                env = mx_strdup("\0");
            }
            else {
                env = mx_strdup(env_val);
            }

            *str = mx_replace_substr(*str, str_to_replace, env);

            free(env);
            free(str_to_replace);
            free(str_var);

        }

        ptr = strchr(*str, '$');
    }

    ptr = strchr(*str, '$');

    if (!ptr) {
        return 0;
    }

    while (ptr != NULL) {

        if (*(ptr + 1) == '(') {

            ptr = strchr(++ptr, '$');
            continue;

        }

        char *tmp_ptr = ptr;

        if (*(ptr + 1) == '{') {

            int ptr_len = mx_strlen(ptr) + 2;
            char *str_to_replace = mx_strnew(ptr_len);
            char *str_var = mx_strnew(ptr_len);

            str_to_replace[0] = *tmp_ptr;
            str_to_replace[1] = *(tmp_ptr + 1);
            tmp_ptr += 2;

            for (int i = 2, j = 0; *tmp_ptr != '}'; i++, j++) {

                str_to_replace[i + 1] = '\0';
                str_var[j + 1] = '\0';

                str_to_replace[i] = *tmp_ptr;

                if (*tmp_ptr != '}') {
                    str_var[j] = *tmp_ptr;
                }


                if (*tmp_ptr == ' ' || *tmp_ptr == '\0') {

                    mx_printerr("ush: bad substitution\n");
                    free(str_to_replace);
                    free(str_var);
                    t_global.exit_status = 1;
                    return -1;

                }

                tmp_ptr++;

                if (*tmp_ptr == '}') {
                    str_to_replace[i + 1] = *tmp_ptr;
                }

            }

            char *env_val = getenv(str_var);
            char *env = NULL;

            if (env_val == NULL) {
                env = mx_strdup("\0");
            }
            else {
                env = mx_strdup(env_val);
            }

            *str = mx_replace_substr(*str, str_to_replace, env);

            free(env);
            free(str_to_replace);
            free(str_var);

        }

        ptr = strchr(*str, '$');

        if (ptr == tmp_ptr) {
            ptr = strchr(++ptr, '$');
        }
    }

    ptr = strrchr(*str, '$');

    if (!ptr) {
        return 0;
    }
    
    while (ptr != NULL) {

        if (*(ptr + 1) != '(') {

            ptr = strchr(++ptr, '$');
            continue;

        }

        char *tmp_ptr = ptr;
        int ptr_len = mx_strlen(ptr) + 2;
        char *str_to_replace = mx_strnew(ptr_len);
        char *str_var = mx_strnew(ptr_len);

        str_to_replace[0] = *tmp_ptr;
        str_to_replace[1] = *(tmp_ptr + 1);
        tmp_ptr += 2;

        for (int i = 2, j = 0; *tmp_ptr != ')'; i++, j++) {

            str_to_replace[i + 1] = '\0';
            str_var[j + 1] = '\0';

            str_to_replace[i] = *tmp_ptr;

            if (*tmp_ptr != ')') {
                str_var[j] = *tmp_ptr;
            }

            tmp_ptr++;

            if (*tmp_ptr == ')') {
                str_to_replace[i + 1] = *tmp_ptr;
            }

        }

       
        char *income_command = mx_strnew(mx_strlen(str_var));

        for (int j = 0; str_var[j] != ' ' && str_var[j] != '\0' && str_var[j] != ')'; j++) {

            char c = str_var[j];
            char z = c;

            if (mx_isalpha(c) && c < 97) {
                c += 32;
            }

            income_command[j] = z;
            str_var[j] = c;

        }

        char *command = exe_cmd_own(str_var);

        if (mx_strlen(command) == 0) {

            mx_printerr("ush: command not found: ");
            mx_printerr(income_command);
            mx_printerr("\n");

        }

        FILE *fp;
        char *strreplace = mx_strnew(PATH_MAX);
        fp = popen(command, "r");

        if (fp == NULL) {

            mx_printerr("Failed to run command\n");
            return 1;

        }

        char *strrep_ptr = strreplace;

        while (fgets(strrep_ptr, PATH_MAX, fp) != NULL) {

            strrep_ptr = strreplace + mx_strlen(strreplace);
            strreplace[mx_strlen(strreplace) - 1] = ' ';

        }

        strreplace[mx_strlen(strreplace) - 1] = '\0';
        pclose(fp);
        
        *str = mx_replace_substr(*str, str_to_replace, strreplace);
        free(strreplace);
        free(command);
        free(income_command);

        free(str_to_replace);
        free(str_var);
        ptr = strrchr(*str, '$');

    }

    return 0;
}


