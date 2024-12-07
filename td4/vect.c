#include "vect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vect_t vect_new(unsigned int n,void (*print_data)(void*,FILE*), void* (*delete_data)(void*),int (*equal_data)(void*,void*)) {
    vect_t vect;

    if ((vect=malloc(sizeof(*vect))) == NULL)
        return NULL;

    vect->max_size = n;
    vect->actual_size=0;
    vect->delete_data=delete_data;
    vect->fprint_data=print_data;
    vect->equal_data=equal_data;

    if ((vect->data=calloc(n,sizeof(*(vect->data)))) == NULL) {
        free(vect);
        return NULL;
    }

    return vect;
}

vect_t vect_append(void* e, vect_t table) {
    if (table==NULL) return NULL;
    if (table->actual_size == table->max_size-1) {
        table->max_size *= 2;
        table->data=realloc(table->data, table->max_size*sizeof(*(table->data)));
    }
    table->data[table->actual_size]=e;
    table->actual_size++;
    return table;
}

vect_t vect_delete(vect_t table){
    if (table==NULL) return NULL;
    for (int i = 0; i < table->actual_size; i++) {
        table->delete_data(table->data[i]);
    }
    free(table->data);
    free(table);
    return NULL;
}

int vect_find(void* param, vect_t l){
    for(int i=0;i<l->actual_size; i++){
        if(l->equal_data((l->data[i]), param) == 0)
            return i;
    }
    return -1;
}

vect_t vect_remove_at(int i, vect_t table){
    for (int j=i; j<table->actual_size-1; j++) {
      table->data[j]=table->data[j+1];
    }
    table->actual_size--;

    if (table->actual_size != 0 && table->actual_size <= table->max_size / 3) {
        table->max_size /= 2;
        table->data=realloc(table->data, table->max_size*sizeof(*(table->data)));
    }
    return table;
}

void vect_printf(vect_t table) {
    vect_fprintf(table,stdout);
}

void vect_fprintf(vect_t table,FILE* fp) {
    for (int i = 0; i < table->actual_size; i++) {
        table->fprint_data(table->data[i], fp);
    }
}

double vect_memory_usage(vect_t table) {
    double size = 0;
    for (size_t i = 0; i < table->actual_size; i++)
    {
        size += strlen(table->data[i]);
    }
    return size / 1024 / 1024;
}
