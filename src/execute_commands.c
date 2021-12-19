#include "../inc/ush.h"

int execute_commands(char *command, char **params, char ***commands_arr, int i) {

    if (!mx_strcmp("cd", command)) {

        t_flags_cd cd_flags;
        init_cd_flags(&cd_flags);

        if (!cd_flags_setter(&cd_flags, params)) {
            t_global.exit_status = cd_own(params, &cd_flags);
        }
        else {
            t_global.exit_status = 1;
        }

        return 0;
    }
    else if (!mx_strcmp("echo", command)) {

        t_flags_echo echo_flags;
        init_echo_flags(&echo_flags);

        if (!echo_flags_setter(&echo_flags, params)) {
            t_global.exit_status = echo_own(&echo_flags, &(*commands_arr)[i]);
        }
        else {
            t_global.exit_status = 1;
        }

        return 0;
    }
    else if (!mx_strcmp("env", command)) {

        t_flags_env env_flags;
        init_env_flags(&env_flags);

        if (!env_flags_setter(&env_flags, params)) {
            t_global.exit_status = env_own(&env_flags, params);
        }
        else {
            t_global.exit_status = 1;
        }

        return 0;
    }
    else if (!mx_strcmp("pwd", command)) {

        t_flags_pwd pwd_flags;
        init_pwd_flags(&pwd_flags);

        if (!pwd_flags_setter(&pwd_flags, params)) {
            t_global.exit_status = pwd_own(&pwd_flags);
        }
        else {
            t_global.exit_status = 1;
        }
        return 0;
    }
    else if (!mx_strcmp("unset", command)) {

        if (unset_check_parameters_own(params) == 0) {
        
            for (int i = 1; params[i] != NULL; i++) {

                if (unset_own(params[i]) < 0) {

                    perror("ush: unset");
                    t_global.exit_status = 1;
                    continue;

                }
            }
            
        }
        return 0;
    }
    else if (!mx_strcmp("which", command)) {

        t_flags_which which_flags;
        init_which_flags(&which_flags);

        if (!which_flags_setter(&which_flags, params)) {
            t_global.exit_status = which_own(&which_flags, params);
        }
        else {
            t_global.exit_status = 1;
        }

        return 0;
    }
    else if (!mx_strcmp("export", command)) {

        if (params[1] == NULL) {

            t_flags_env env_flags;
            init_env_flags(&env_flags);
            env_own(&env_flags, params);
            t_global.exit_status = 0;

            return 0;

        }

        for (int i = 1; params[i] != NULL; i++) {

            char *ptr = mx_strchr(params[i], '=');

            if (ptr == NULL) {
                continue;
            }
            
            char **arr = mx_strsplit(params[i], '=');
            setenv(arr[0], arr[1], 1);
            mx_del_strarr(&arr);

        }

        t_global.exit_status = 0;
        return 0;
    }
    else if (!mx_strcmp("fg", command)) {

        if (params[1] == NULL) {
            return 0;
        }
        
        t_jobs *node = jobs;
        while (node != NULL && node->job_id != mx_atoi(params[1])) {
            node = node->next;
        }
        
        if (node == NULL) {

            mx_printerr("ush: fg: no such job\n");
            t_global.exit_status = 1;
            return 0;

        }

        kill(node->pid, SIGCONT);
        int child_status = 0;
        waitpid(node->pid, &child_status, WUNTRACED);
        t_global.exit_status = WEXITSTATUS(child_status);

        if (!WIFSTOPPED(child_status)) {
            jobs_remove(&jobs, node->pid);
        }
            
        if (WIFSIGNALED(child_status)) {
            t_global.exit_status = 130;
        }
        else {
            t_global.exit_status = 0;
        }

        return 0;
    }
    else if (!mx_strcmp("exit", command)) {

        int ext_val = 0;

        if (params[1] != NULL) {
            ext_val = mx_atoi(params[1]);
        }

        free(command);
        mx_del_strarr(&params);
        mx_del_strarr(commands_arr);

        exit(ext_val);
    }

    return -1;
}


