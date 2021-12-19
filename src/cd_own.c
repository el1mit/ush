#include "../inc/ush.h"

static void way_to_parent() {

    char* p = strrchr(t_global.PWD, '/');

    if (p) {
        mx_memset(p, '\0', mx_strlen(p));
    }
    else {
        t_global.PWD[0] = '/';
    }

    if (t_global.PWD[0] == '\0') {
        t_global.PWD[0] = '/';
    }
}

static void way_to_dir(char* dirrectory) {

    int l = mx_strlen(t_global.PWD);

    if (t_global.PWD[l - 1] != '/') {
        t_global.PWD[mx_strlen(t_global.PWD)] = '/';
    }

    mx_memcpy(t_global.PWD + mx_strlen(t_global.PWD), dirrectory, mx_strlen(dirrectory));

}

static int check_path_lnk(char* path) {

    char lnk_PWD[PATH_MAX];
    mx_memcpy(lnk_PWD, t_global.PWD, PATH_MAX);

    if (path[0] == '/') {

        memset(t_global.PWD, 0, PATH_MAX);
        t_global.PWD[0] = '/';

    }

    char buff[PATH_MAX];
    memset(buff, 0, PATH_MAX);
    ssize_t nb = 0;
    char** lnk_arr = mx_strsplit(path, '/');

    for (int i = 0; lnk_arr[i] != NULL; i++) {

        if (!mx_strcmp(lnk_arr[i], "..")) {
            way_to_parent();
        }
        else if (mx_strcmp(lnk_arr[i], ".")) {
            way_to_dir(lnk_arr[i]);
        }

        nb = readlink(t_global.PWD, buff, PATH_MAX);

        if (nb > 0 && mx_strcmp(lnk_arr[i], "..") && mx_strcmp(lnk_arr[i], ".")) {

            mx_del_strarr(&lnk_arr);
            mx_memcpy(t_global.PWD, lnk_PWD, PATH_MAX);
            return 1;

        }

        mx_memset(buff, 0, mx_strlen(buff));
    }

    mx_del_strarr(&lnk_arr);

    int status = chdir(t_global.PWD);

    if (status < 0) {

        mx_printerr("cd: ");
        char* err_tmp = mx_strdup(strerror(errno));

        if (err_tmp[0] < 97) {
            err_tmp[0] += 32;
        }

        mx_printerr(err_tmp);
        free(err_tmp);
        mx_printerr(": ");
        mx_printerr(path);
        mx_printerr("\n");

        mx_memcpy(t_global.PWD, lnk_PWD, PATH_MAX);

    }
    else {

        if (mx_strcmp(t_global.OLDPWD, lnk_PWD)) {

            mx_memcpy(t_global.OLDPWD, lnk_PWD, PATH_MAX);
            status = setenv("OLDPWD", t_global.OLDPWD, 1);

        }

        status = setenv("PWD", t_global.PWD, 1);
    }

    return 0;
}

int cd_own(char **parameters, t_flags_cd *flags) {

    escape_sequences(&parameters);
    int argc = 0;

    while(parameters[argc]) {
        argc++;
    }

    char real_buf[PATH_MAX];
    char *path = NULL;

    char tmp_PWD[PATH_MAX];
    mx_memcpy(tmp_PWD, t_global.PWD, PATH_MAX);

    if (argc > 1) {

        if (parameters[1][0] == '-' && mx_strlen(parameters[1]) > 1) {
            path = mx_strdup(parameters[2]);
        }
        else {
            path = mx_strdup(parameters[1]);
        }

    }

    switch (argc)
    {
    case 1:

        if (t_global.HOME[0] != '\0') {

            chdir(t_global.HOME);

            if (mx_strcmp(t_global.OLDPWD, t_global.PWD)) {

                mx_memcpy(t_global.OLDPWD, t_global.PWD, PATH_MAX);
                setenv("OLDPWD", t_global.OLDPWD, 1);

            }

            mx_memcpy(t_global.PWD, t_global.HOME, PATH_MAX);
            setenv("PWD", t_global.PWD, 1);
        }

        free(path);
        return 0;

        break;

    case 2:

        if (parameters[1][0] == '-' && mx_strlen(parameters[1]) > 1) {

            if (t_global.HOME[0] != '\0') {

                chdir(t_global.HOME);

                if (mx_strcmp(t_global.OLDPWD, t_global.PWD)) {

                    mx_memcpy(t_global.OLDPWD, t_global.PWD, PATH_MAX);
                    setenv("OLDPWD", t_global.OLDPWD, 1);

                }

                mx_memcpy(t_global.PWD, t_global.HOME, PATH_MAX);
                setenv("PWD", t_global.PWD, 1);

            }

            free(path);
            return 0;

        }
        else  if (parameters[1][0] == '-') {

            if (t_global.OLDPWD[0] != '\0') {

                chdir(t_global.OLDPWD);
                setenv("OLDPWD", t_global.PWD, 1);
                setenv("PWD", t_global.OLDPWD, 1);

                mx_memcpy(t_global.PWD, t_global.OLDPWD, PATH_MAX);
                mx_memset(t_global.OLDPWD, 0, PATH_MAX);
                mx_memcpy(t_global.OLDPWD, getenv("OLDPWD"), mx_strlen(getenv("OLDPWD")));

                char *test_own = mx_strrep(t_global.PWD, t_global.HOME, TILDA);

                if (test_own != NULL) {
                    free(test_own);
                }

            }

            free(path);
            return 0;

        }
        break;

    case 3:

        if (parameters[1][0] == '-') {
            break;
        }
        else {

            char *tmp_own = mx_strrep(t_global.PWD, parameters[1], parameters[2]);

            if (tmp_own != NULL) {

                free(path);
                path = tmp_own;

            }
            else {

                mx_printerr("cd: string not in pwd: ");
                mx_printerr(parameters[1]);
                mx_printerr("\n");
                return 1;

            }
        }

        break;

    case 4:

        if (parameters[1][0] != '-') {

            mx_printerr("ush: cd: too many arguments\n");
            free(path);
            return 1;

        }
        else {

            char *tmp_own = mx_strrep(t_global.PWD, parameters[2], parameters[3]);

            if (tmp_own != NULL) {

                free(path);
                path = tmp_own;

            }
            else {

                mx_printerr("cd: string not in pwd: ");
                mx_printerr(parameters[1]);
                mx_printerr("\n");
                return 1;

            }
        }

        break;

    default:
        break;
    }

    char *tilda_path_own = mx_replace_substr(path, "~", t_global.HOME);

    if (tilda_path_own == NULL) {
        tilda_path_own = mx_strdup(path);
    }

    if (flags->flag_s) {

        if (check_path_lnk(tilda_path_own)) {

            mx_printerr("cd: not a directory: ");
            mx_printerr(tilda_path_own);
            mx_printerr("\n");

            if (path != NULL) {
                free(path);
            }

            free(tilda_path_own);
            return 1;

        }

        if (path != NULL) {
            free(path);
        }

        free(tilda_path_own);
        return 0;

    }

    if (path != NULL && flags->flag_P) {

        char *resulting = NULL;
        resulting = realpath(tilda_path_own, real_buf);
        free(tilda_path_own);
        tilda_path_own = mx_strdup(real_buf);
        
        if (!resulting) {
            free(resulting);
        }
    }

    int own_status;

    if (tilda_path_own[0] == '/') {

        mx_memset(t_global.PWD, '\0', mx_strlen(t_global.PWD));
        t_global.PWD[0] = '/';

    }

    char **arr = mx_strsplit(tilda_path_own, '/');

    for (int i = 0; arr[i] != NULL; i++) {

        if (!mx_strcmp(arr[i], "..")) {
            way_to_parent();
        }
        else if (mx_strcmp(arr[i], ".")) {
            way_to_dir(arr[i]);
        }
    }

    mx_del_strarr(&arr);

    own_status = chdir(t_global.PWD);

    if (own_status < 0) {

        mx_printerr("cd: ");
        char *err_tmp = mx_strdup(strerror(errno));

        if (err_tmp[0] < 97) {
            err_tmp[0] += 32;
        }

        mx_printerr(err_tmp);
        free(err_tmp);
        mx_printerr(": ");
        mx_printerr(path);
        mx_printerr("\n");
        mx_memcpy(t_global.PWD, tmp_PWD, PATH_MAX);

        return 1;

    }
    else {

        if (mx_strcmp(t_global.OLDPWD, tmp_PWD)) {

            mx_memcpy(t_global.OLDPWD, tmp_PWD, PATH_MAX);
            own_status = setenv("OLDPWD", t_global.OLDPWD, 1);

        }

        own_status = setenv("PWD", t_global.PWD, 1);
    }

    if (path != NULL) {
        free(path);
    }

    free(tilda_path_own);
    return 0;

}

