#include "../inc/ush.h"

void init_global_own(void) {

    t_global.PWD = mx_strnew(PATH_MAX);
    t_global.PWD = mx_strcpy(t_global.PWD, getenv("PWD"));

    t_global.OLDPWD = mx_strnew(PATH_MAX);
    char *sys_var = getenv("OLDPWD");

    if (sys_var != NULL) {
        t_global.OLDPWD = mx_strcpy(t_global.OLDPWD, sys_var);
    }

    t_global.HOME = mx_strnew(PATH_MAX);
    sys_var = getenv("HOME");

    if (sys_var != NULL) {
        t_global.HOME = mx_strcpy(t_global.HOME, sys_var);
    }

    t_global.PATH = mx_strnew(PATH_MAX);
    sys_var = getenv("PATH");

    if (sys_var != NULL) {
        t_global.PATH = mx_strcpy(t_global.PATH, sys_var);
    }

    jobs = jobs_create(getpid(), "ush");

    int oshlvl = mx_atoi(getenv("SHLVL"));
    setenv("SHLVL", mx_itoa(oshlvl + 1), 1);

    char *arr = mx_strjoin(t_global.PWD, "/");
    arr = mx_strjoin(arr, "ush");
    setenv("SHELL", arr, 1);
    free(arr);
}

void free_global_own(void) {

    free(t_global.HOME);
    free(t_global.PATH);
    free(t_global.PWD);
    free(t_global.OLDPWD);
    jobs_clear(&jobs);

}

