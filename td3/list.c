#include "list.h"

list_t list_new(void (*fprint_data)(void*,FILE*),void* (*delete_data)(void*), int (*equal_data)(void*,void*)) {
    list_t list;

    if ((list=malloc(sizeof(*list))) == NULL)
        return NULL;


    if ((list->data=calloc(1,sizeof(*(list->data)))) == NULL) {
        free(list);
        return NULL;
    }

    list->delete_data=delete_data;
    list->equal_data=equal_data;
    list->fprint_data=fprint_data;
    list->size=0;
    return list;
}

int list_is_empty(list_t l) {
    if(l->size == 0) {
        return 1;
    }
    return 0;
}

int link_is_empty(link_t l) {
    if(l->data == NULL) {
        return 1;
    }
    return 0;
}

void* list_first(list_t l) {    
    return l->data->data;
}

link_t link_add_first(void* e, link_t l) {
    link_t new_link;

    if ((new_link=malloc(sizeof(*new_link))) == NULL)
        return NULL;
    
    if ((new_link->data=calloc(1,sizeof(*(new_link->data)))) == NULL) {
        free(new_link);
        return NULL;
    }

    new_link->next = l;
    new_link->data = e; 
    return new_link;
}

list_t list_add_first(void* e, list_t l) {
    l->data = link_add_first(e, l->data);
    l->size++;
    return l;
}

list_t list_del_first(list_t l) {
    if (l==NULL) return NULL;
    l->data = link_del_first(l->data, l->delete_data);
    l->size--;
    return l;
}

link_t link_del_first(link_t l , void* (*delete)(void*)) {
    link_t new_tete = l->next;
    if (l==NULL) return NULL;
    delete(l->data);
    free(l);
    return new_tete;
}

size_t list_length(list_t l) {
    return l->size;
}

void list_fprintf(list_t l, FILE* fp) {
    link_t current_link;
    current_link = l->data;
    for(int i=0; i<l->size; i++) {
        l->fprint_data(current_link->data, fp);
        current_link = current_link->next;
    }
    fprintf(fp, "\n");
}

void list_printf(list_t l) {
    list_fprintf(l, stdout);
    printf("\n");
}

list_t list_delete(list_t l) {
    link_t link, next_link;
    link = l->data;

    for (int i=0; i<l->size; i++) {
        next_link = link->next;
        l->delete_data(link->data);
        free(link);
        link = next_link;
    }
    
    l->size=0;
    return l;
}

list_t list_add_last(void* e, list_t l) {
    link_t current_link = l->data;

    for (int i=0; i<l->size-1; i++) {
        current_link = current_link->next;
    }
    current_link->next = link_add_last(e, current_link);
    l->size++;
    return l;
}

link_t link_add_last(void* e, link_t l) {
    link_t new_link;

    if ((new_link=malloc(sizeof(*new_link))) == NULL)
        return NULL;
    
    if ((new_link->data=calloc(1,sizeof(*e))) == NULL) {
        free(new_link);
        return NULL;
    }
    
    new_link->data = e;
    return new_link;
}

list_t list_del_last(list_t l) {
    link_t current_link;
    current_link = l->data;

    for (int i=0; i<l->size-1; i++) {
        current_link = current_link->next;
    }

    current_link = link_del_last(current_link, l->delete_data);
    l->size--;
    return l;
}

link_t link_del_last(link_t l, void* (*delete)(void*)) {
    delete(l->data);
    free(l);
    return l;
}

link_t list_lookup(void* elem, list_t l, int(*compare)(void* e1, void* e2)) {
    link_t current_link;
    current_link = l->data;

    for (int i=0; i<l->size; i++) {
        if(compare(current_link->data, elem)) {
            return current_link;
        }
        current_link = current_link->next;
    }
    return NULL;
}

link_t list_find(void* e, list_t l) {
    link_t current_link;
    current_link = l->data;    for (int i=0; i<l->size; i++) {
        if(l->equal_data(current_link->data, e)) {
            return current_link;
        }
        current_link = current_link->next;
    }
    return NULL;
}

list_t list_remove(void* param, list_t l) {
    link_t current_link;
    link_t next_link;
    
    current_link = list_find(param, l);
    next_link = current_link->next;
    
    free(current_link);
    current_link = next_link;
    l->size--;
    return l;
}

void list_simple_visit(list_t l, void (*exec_on_value)(void*,void*), void* param) {
    link_t current_link;
    current_link = l->data;

    for (int i=0; i<l->size; i++) {
        exec_on_value(current_link->data, param);
        current_link = current_link->next;
    }
}

double list_memory_usage(list_t l) {
    double size = 0;
    link_t current_link;
    current_link = l->data;

    for (int i=0; i<l->size; i++) {
        size += sizeof(current_link->data);
        current_link = current_link->next;
    }
    return size;
}
// void list_visit(list_t l, int (*exec_on_value)(void*,void*), int (*exec_on_link)(list_t,void*),void* param) {

// }

