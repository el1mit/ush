#include "../inc/ush.h"

void create_process_own(char *cmnd, char **parameters, char *str) {

    int ch_p;

    if ((ch_p = fork()) == 0) {

        if (getenv("PATH") == NULL) {
            mx_printerr("ush: command not found: ");
            mx_printerr(cmnd);
            mx_printerr("\n");
            exit(1);
        }

        char **path_dir_own = mx_strsplit(getenv("PATH"), ':');

        for (int i = 0; path_dir_own[i] != NULL; i++) {

            int exec_status = 0;
            char *cmd = NULL;

            if (cmnd[0] != '/') {
                cmd = mx_strjoin(path_dir_own[i], "/");
                cmd = mx_strjoin(cmd, cmnd);
            }
            else {
                cmd = mx_strdup(cmnd);
            }

            exec_status = execve(cmd, parameters, environ); 
            free(cmd);

            if (exec_status != -1) {

                mx_del_strarr(&path_dir_own);
                exit(0);

            }
        }

        mx_printerr("ush: command not found: ");
        mx_printerr(cmnd);
        mx_printerr("\n");
        mx_del_strarr(&path_dir_own);
        exit(1);

    }
    else {

        t_jobs *n_process = jobs_create(ch_p, str);
        jobs_push_back(&jobs, &n_process);
        int child_status = 0;
        waitpid(ch_p, &child_status, WUNTRACED);
        t_global.exit_status = WEXITSTATUS(child_status);

        if (!WIFSTOPPED(child_status)) {
            jobs_remove(&jobs, ch_p);
        }
        else {
            t_global.exit_status = 147;
        }
        
        if (WIFSIGNALED(child_status)) {
            t_global.exit_status = 130;
        }
    }
}
