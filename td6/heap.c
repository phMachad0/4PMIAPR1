#include "heap.h"
#include "swap.h"

heap_t heap_new(unsigned int n,void (*print_data)(void*,FILE*),
                void* (*delete_data)(void*),int (*equal_data)(void*,void*)) {
    return vect_new(n,print_data,delete_data,equal_data);
}

int heap_is_empty(heap_t tas) {
    return tas->actual_size == 0;
}

int heap_add(void* valeur, heap_t tas) {
    if (heap_is_empty(tas)) {
        vect_append(valeur,tas);
        return 0;
    }
    vect_append(valeur,tas);
    int i = tas->actual_size-1;
    while (i != 0 && tas->equal_data(tas->data[i],tas->data[HEAP_FATHER(i)]) < 0) {
        swap(&(tas->data[i]),&(tas->data[HEAP_FATHER(i)]));
        i = HEAP_FATHER(i);
    }
    return 0;
}

void* heap_get_extrema(heap_t tas) {
    return tas->data[0];
}

int heap_delete_extrema(heap_t tas) {
    if (heap_is_empty(tas)) {
        return -1;
    }
    void* extrema = tas->data[0];
    swap(&(tas->data[0]),&(tas->data[tas->actual_size-1]));
    tas->actual_size--;
    int i = 0;
    while (HEAP_LEFTSON(i) < tas->actual_size) {
        int min = HEAP_LEFTSON(i);
        if (HEAP_RIGHTSON(i) < tas->actual_size && tas->equal_data(tas->data[HEAP_RIGHTSON(i)],tas->data[min]) < 0) {
            min = HEAP_RIGHTSON(i);
        }
        if (tas->equal_data(tas->data[i],tas->data[min]) < 0) {
            break;
        }
        swap(&(tas->data[i]),&(tas->data[min]));
        i = min;
    }
    // tas->delete_data(extrema);
    return 0;
}

int heap_verification(heap_t tas) {
    for (int i = 0; i < tas->actual_size; i++) {
        if (HEAP_LEFTSON(i) < tas->actual_size && tas->equal_data(tas->data[i],tas->data[HEAP_LEFTSON(i)]) > 0) {
            return -1;
        }
        if (HEAP_RIGHTSON(i) < tas->actual_size && tas->equal_data(tas->data[i],tas->data[HEAP_RIGHTSON(i)]) > 0) {
            return -1;
        }
    }
    return 0;
}

heap_t heap_delete(heap_t tas) {
    return vect_delete(tas);
}

void heap_printf(heap_t tas) {
    vect_printf(tas);
}

void heap_fprintf(heap_t tas,FILE* fp) {
    vect_fprintf(tas,fp);
}