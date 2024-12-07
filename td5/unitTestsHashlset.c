#include <stdio.h>
#include "hashlset.h"
#include "../td4/double.h"

unsigned int double_hashage(void* e) {
    return *(double*)e;
}

int main() {
	// Pile de double
	hashlset_t hs1=hashlset_new(5,double_hashage,double_fprintf,double_delete,double_equal);
	hashlset_fprintf(hs1, stdout);
	// double* pv;
	printf("Ajout de 1,2,3,4,5,6,7 : \n");
	hashlset_put(double_new(1),hs1);
	hashlset_put(double_new(2),hs1);
    hashlset_put(double_new(3),hs1);
	// pv=double_new(4);
    // hashlset_put(pv,hs1);
	hashlset_put(double_new(5),hs1);
	hashlset_put(double_new(6),hs1);
	hashlset_put(double_new(7),hs1);

	hashlset_fprintf(hs1, stdout);

	// printf("Defiler :%lf\n",*pv);
	// hashlset_remove_key(pv, hs1);

	// double_delete(pv);
	hashlset_fprintf(hs1, stdout);

    // pv=double_new(3);
	// hashlset_remove_key(pv, hs1);
	// printf("Defiler :%lf\n",*pv);
	// double_delete(pv);
	hashlset_fprintf(hs1, stdout);

	printf("Liberation de la queuee\n");
	hs1=hashlset_delete(hs1);
    free(hs1);

	return EXIT_SUCCESS;
}