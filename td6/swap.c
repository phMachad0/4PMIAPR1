#include "swap.h"
int swap(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}