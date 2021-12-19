#include "../inc/libmx.h"

void mx_push_back(t_list** list, void* data) {
    t_list* back = mx_create_node(data);
    t_list* temp = NULL;

    if (!list || !(*list)) {
        *list = back;
    }
    else {
        temp = *list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = back;
    }
}

