#include "list.h"
#include "double.h"

// Affichage d'une chaine de type mystring
void double_fprintf(void* val,FILE* fp) { 
    fprintf(fp,"%lf ",*(double*)val);
}
void double_printf(void* val)  {
    double_fprintf(val,stdout);
}

// Test l'egalite de 2 reels
int double_equal(void* pv1, void* pv2) {
    if(*(double*)pv1 == *(double*)pv2)
		return 0;
	else if (*(double*)pv1 < *(double*)pv2)
		return -1;
	else
		return 1;
}

// Génération d'un reel aléatoire
void double_random(double* p) {
    *p=random()%100;
}

// Clone d'un reel
double* double_new(double val) { 
    double*p = malloc(sizeof(*p));
    *p=val;
    return p;
}

void* double_delete(void *data) {
    if (data != NULL) {
        free(data);
    }
    return NULL;
}
