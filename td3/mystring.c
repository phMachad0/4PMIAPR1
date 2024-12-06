#include "mystring.h"


// Affichage d'une chaine de type mystring
void mystring_fprintf(void* val,FILE* fp) {
    fprintf(fp,"%s ", (mystring)val);
}
void mystring_printf(void* val) { 
    mystring_fprintf(val, stdout);
}

// Liberation d'une chaine de type mystring
void* mystring_delete(void* val) {
    if (val != NULL) {
        free(val);
    }
    return NULL;
}

// Teste si le contenu de 2 chaines sont egales
int mystring_equal(void* pv1, void* pv2) { 
    return strcasecmp((mystring)pv1,(mystring)pv2); 
}

// Cree avec alocation dynamique une chaine contenant AleaXX
void mystring_random(mystring* p) {
  char tmp[256];
  sprintf(tmp,"Alea%ld",random()%100);
  *(mystring*)p=strdup(tmp);
}

// Allocation et copie d'une chaine à partir d'une autre
void* mystring_new(mystring val) {
    mystring*s = malloc(sizeof(*val));
    *s=val;
    return s;
}

