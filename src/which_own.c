#include "../inc/ush.h"

int which_own(t_flags_which *flags, char **data_own) {

    escape_sequences(&data_own);
    DIR *d;
    struct dirent *dirrectory;
    struct stat sb_own;
    bool is_found = false;
    bool is_here = true;

    char *builtins[8] = {"cd", "pwd", "env", "which", "echo", "exit", "unset", "fg"};

    if (flags->flag_A) {

        int i = 2;

        if (data_own[i] == NULL) {
            return 1;
        }

        char *name = NULL;
        char **path_dir = mx_strsplit(getenv("PATH"), ':');

        while (data_own[i] != NULL) {

            for (int z = 0; z < 8; z++) {

                if (mx_strcmp(builtins[z], data_own[i]) == 0) {

                    mx_printerr(data_own[i]);
                    mx_printerr(": ush built-in command\n");
                    is_found = true;
                    break;

                }
            }

            if (mx_strcmp(data_own[i], "export") == 0) {

                mx_printerr("export: ush reserved word\n");
                is_found = true;
            }

            if (data_own[i][0] == '/') {

                lstat(data_own[i], &sb_own);

                if (sb_own.st_mode & S_IXUSR) {

                    mx_printstr(data_own[i]);
                    mx_printstr("\n");
                    is_found = true;

                }
                else {

                    mx_printerr(data_own[i]);
                    mx_printerr(" not found\n");
                    i++;
                    is_found = true;
                    is_here = false;
                    continue;

                }
            }

            for (int j = 0; path_dir[j] != NULL; j++) {

                d = opendir(path_dir[j]);

                if (d != NULL) {

                    while ((dirrectory = readdir(d)) != NULL) {

                        if (mx_strcmp(dirrectory->d_name, data_own[i]) == 0) {

                            name = mx_strnew(256);
                            mx_strcpy(name, path_dir[j]);
                            name = mx_strcat(name, "/");
                            name = mx_strcat(name, data_own[i]);
                            mx_printstr(name);
                            mx_printstr("\n");
                            free(name);
                            is_found = true;
                            break;

                        }       
                    }
                    closedir(d);
                }
            }

            if (is_found == false) {

                is_here = false;
                mx_printerr(data_own[i]);
                mx_printerr(" not found\n");

            }

            i++;
        }

        mx_del_strarr(&path_dir);

        if (!is_here) {
            return 1;
        }

        return 0;

    }
    else if (data_own[1] != NULL) {

        int i = 1;

        if (flags->flag_S) {
            i = 2;
        }
        
        if (data_own[i] == NULL) {
            return 1;
        }
            
        char *name = NULL;
        char **path_dir = mx_strsplit(getenv("PATH"), ':');

        while (data_own[i] != NULL) {

            int built = 0;

            for (int z = 0; z < 8; z++) {

                if (!mx_strcmp(builtins[z], data_own[i])) {

                    mx_printerr(data_own[i]);
                    mx_printerr(": ush built-in command\n");
                    is_found = true;
                    built = 1;
                    i++;
                    break;

                }
            }

            if (built) {

                built = 0;
                is_found = false;
                continue;

            }
            if (!mx_strcmp(data_own[i], "export")) {

                mx_printerr("export: ush reserved word\n");
                is_found = true;
                i++;

                continue;

            }

            if (data_own[i][0] == '/') {

                lstat(data_own[i], &sb_own);

                if (sb_own.st_mode & S_IXUSR) {

                    mx_printstr(data_own[i]);
                    mx_printstr("\n");
                    i++;
                    is_found = true;
                    continue;

                }
                else {

                    mx_printerr(data_own[i]);
                    mx_printerr(" not found\n");
                    i++;
                    is_found = true;
                    is_here = false;
                    continue;

                }
            }

            for (int j = 0; path_dir[j] != NULL; j++) {

                d = opendir(path_dir[j]);

                if (d != NULL) {

                    while ((dirrectory = readdir(d)) != NULL) {

                        if (!mx_strcmp(dirrectory->d_name, data_own[i])) {

                            name = mx_strnew(256);
                            mx_strcpy(name, path_dir[j]);
                            name = mx_strcat(name, "/");
                            name = mx_strcat(name, data_own[i]);
                            mx_printstr(name);
                            mx_printstr("\n");
                            free(name);
                            is_found = true;
                            break;

                        }       
                    }

                    closedir(d);
                }
            }

            if (is_found == false) {

                is_here = false;
                mx_printerr(data_own[i]);
                mx_printerr(" not found\n");

            }

            is_found = false;
            i++;

        }

        mx_del_strarr(&path_dir);

        if (is_here) {
            return 0;
        }

        return 1;
    }
    else
        return 1;
}

