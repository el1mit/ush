#include "../inc/libmx.h"

int mx_list_size(t_list* list) {
    int count = 0;
    t_list* temp = NULL;

    if (list) {
        temp = list;
        while (temp != NULL) {
            temp = temp->next;
            count++;
        }
    }
    return count;
}

