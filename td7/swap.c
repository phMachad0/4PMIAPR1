#include "swap.h"

void swap(char **pos1, char **pos2) {

    char *temp = *pos1;
    *pos1 = *pos2;
    *pos2 = temp;
    
}