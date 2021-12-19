#include "../inc/ush.h"

t_jobs *jobs_create(int pid, char *cmd) {

    t_jobs *result = (t_jobs *)malloc(sizeof(t_jobs));

    result->pid = pid;
    result->job_id = 0;
    result->cmd = mx_strdup(cmd);
    result->next = NULL;
    result->prev = NULL;

    return result;
}

void jobs_push_back(t_jobs **list, t_jobs **data_own) {

    t_jobs *tmp = NULL;

    if (list == NULL || *list == NULL) {

        *list = *data_own;
        (*list)->next = NULL;
        (*list)->prev = NULL;

    }
    else {

        tmp = *list;

        while (tmp->next != NULL) {
            tmp = tmp->next;
        }

        (*data_own)->prev = tmp;
        tmp->next = *data_own;
        tmp->next->prev = tmp;
        tmp->next->next = NULL;
        (*list)->prev = tmp->next;

    }
}

int jobs_remove(t_jobs **h, int pid) {

    t_jobs *n = *h;

    while (n->next->pid != pid && n->next != NULL) {
        n = n->next;
    }

    t_jobs *tmp = NULL;

    if (n->next != NULL) {
        tmp = n->next->next;
    }

    free(n->next->cmd);
    free(n->next);
    n->next = tmp;

    if (tmp != NULL) {
        n->next->prev = n;
    }

    return 0;
}

void jobs_clear(t_jobs **h) {

    t_jobs *temp = *h;

    while (temp != NULL) {

        t_jobs *tmp = temp->next;

        if (temp->pid != getpid()) {
            kill(temp->pid, SIGINT);
        }

        free(temp->cmd);
        free(temp);
        temp = tmp;

    }

    *h = NULL;
}
