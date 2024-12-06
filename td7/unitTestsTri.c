#include "tri.h"
#include "../td3/mystring.h"
#include "../td4/double.h"

char** randomchartabgeneration(unsigned n) {
	char tmp[256];
	char** donnees_test = malloc(n * sizeof(*donnees_test));
	for (size_t i = 0; i < n; i++) {
		sprintf(tmp,"Alea%ld",random()%n);
		donnees_test[i] = strdup(tmp);
	}
	return donnees_test;
}

int* int_new(int val) {
	int*p = malloc(sizeof(*p));
	*p=val;
	return p;
}

void int_fprintf(void* val, FILE* fp) {
	fprintf(fp,"%d ",*(int*)val);
}

void* int_delete(void* data) {
	if (data != NULL) {
		free(data);
	}
	return NULL;
}

int int_equal(void* pv1, void* pv2) {
	if(*(int*)pv1 == *(int*)pv2)
		return 0;
	else if (*(int*)pv1 < *(int*)pv2)
		return -1;
	else
		return 1;
}

int testInt() {
	int n = 10;

	vect_t tab = vect_new(n, int_fprintf,int_delete,int_equal);

	for (size_t i = 0; i < n; i++) {
		int *val = int_new(random() % n);
		vect_append(val, tab);
	}

	printf("Tableau initial : ");
	vect_printf(tab);
	printf("\n");

	// mergesort(tab);
	// quicksort(tab);
	heapsort(tab);
	vect_printf(tab);

	printf("\n");
	tab=vect_delete(tab);
	return 0;
}

int testString() {
	// char *donnees_test[] = {"Longtemps", "je", "me", "suis", "couche", "de", "bonne", "heure", "Parfois", "a",
	// 	                "peine", "ma", "bougie", "eteinte"};
    char **donnees_test = randomchartabgeneration(14);
	// int n = sizeof(donnees_test) / sizeof(donnees_test[0]);

	vect_t tab = vect_new(14, mystring_fprintf, mystring_delete, mystring_equal);

	for (size_t i = 0; i < 14; i++) {
		vect_append(donnees_test[i], tab);
	}

	printf("Tableau initial : ");
	vect_printf(tab);
	printf("\n");

	// mergesort(tab);
	// quicksort(tab);
	heapsort(tab);
	vect_printf(tab);
	printf("\n");
	free(donnees_test);
	vect_delete(tab);
	return 0;
}

int main() {
	testInt();
	testString();
	return 0;
}