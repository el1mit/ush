#include "../inc/ush.h"

static void handle_ctrl_c(int s) {

    t_jobs* nod = jobs;

    while (nod->next != NULL) {
        nod = nod->next;
    }

    int _p = nod->pid;

    printf("\n");

    if (_p == jobs->pid) {

        free_global_own();
        exit(130);

    }
    else {
        kill(_p, s);
    }
}

static void handle_ctrl_z(int s) {

    t_jobs* nod = jobs;
    int _id = 0;

    while (nod->next != NULL) {

        if (nod->job_id > _id) {
            _id = nod->job_id;
        }

        nod = nod->next;
    }

    int _p = nod->pid;

    if (_p == jobs->pid) {
        return;
    }

    kill(_p, s);
    _id++;
    nod->job_id = _id;
    printf("[%d]  Stopped\t\t\t%s\n", _id, nod->cmd);

    return;
}

int main(void) {

    char *cmds = NULL;
    char *l = NULL;
    char **pmts = NULL;

    init_global_own();

    while (true) {

        signal(SIGINT, handle_ctrl_c);
        signal(SIGTSTP, handle_ctrl_z);
        
        if (isatty(fileno(stdin))) {
            mx_printstr("u$h> ");
        }

        read_command(&l);

        char **cmds_arr = mx_strsplit(l, ';');

        for (int i = 0; cmds_arr[i] != NULL; i++) {

            char *ptr = cmds_arr[i];
            char *tmp_ptr = ptr;

            while (*tmp_ptr != '\0' && !mx_isalpha(*tmp_ptr)) {

                *tmp_ptr = '\0';

                for (; *(tmp_ptr + 1) != '\0';) {

                    mx_swap_char(tmp_ptr, tmp_ptr + 1);
                    tmp_ptr++;

                }

                tmp_ptr = ptr;
            }
        }

        free(l);
        l = NULL;

        for (int i = 0; cmds_arr[i] != NULL; ++i) {

            if (cmd_substitution_own(&cmds_arr[i]) == -1) {
                continue;
            }

            pmts = mx_strsplit(cmds_arr[i], ' ');
            cmds = mx_strdup(pmts[0]);

            if (execute_commands(cmds, pmts, &cmds_arr, i)) {

                escape_sequences(&pmts);
                create_process_own(cmds, pmts, cmds_arr[i]);

            }

            free(cmds);
            mx_del_strarr(&pmts);

        }

        mx_del_strarr(&cmds_arr);

        if (!isatty(fileno(stdin))) {
            break;
        }
    }

    free_global_own();
    return 0;
}

