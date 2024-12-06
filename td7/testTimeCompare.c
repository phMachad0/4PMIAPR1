#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tri.h"
#include "../td4/vect.h"

int* int_new(int val) {
	int* p = malloc(sizeof(*p));
	*p = val;
	return p;
}

void int_fprintf(void* val, FILE* fp) {
	fprintf(fp, "%d ", *(int*)val);
}

void* int_delete(void* data) {
	if (data != NULL) {
		free(data);
	}
	return NULL;
}

int int_equal(void* pv1, void* pv2) {
	if (*(int*)pv1 == *(int*)pv2)
		return 0;
	else if (*(int*)pv1 < *(int*)pv2)
		return -1;
	else
		return 1;
}

int compar(void* a, void* b) {
	return *(int*)a - *(int*)b;
}

int* randominttabgeneration(unsigned n) {
	int* donnees_test = malloc(n * sizeof(*donnees_test));
	for (size_t i = 0; i < n; i++)
		donnees_test[i] = random() % n;
	return donnees_test;
}

int main() {
	clock_t avant, apres;
	double temps1, temps2, temps3;
	int k, total_number=1000000;
	int *t1, *t2, *t3;

	/* Ouverture d'un fichier contenant les temps de calcul */
	FILE* fp =fopen("tempstri.dat","w");

	/* k est le nombre d’elements a trier */
	for (k = 1; k <= total_number; k += k) {

		/* génération des nombres aléatoires et copie dans le deuxieme tableau */
		t1 = randominttabgeneration(k);
		t2 = malloc(k * sizeof(t2));
		t3 = malloc(k * sizeof(t3));
		memcpy(t2, t1, k * sizeof(*t1));
		memcpy(t3, t1, k * sizeof(*t1));

		vect_t tab1 = vect_new(k, int_fprintf, int_delete, int_equal);

		for (size_t i = 0; i < k; i++) {
			int* val = int_new(t1[i]);
			vect_append(val, tab1);
		}

		/* Tri par quick sort , version de la bibliotheque C */
		avant = clock();
		quicksort(tab1);
		apres = clock();
		temps1 = ((double)apres - avant) / CLOCKS_PER_SEC;

		vect_t tab2 = vect_new(k, int_fprintf, int_delete, int_equal);

		for (size_t i = 0; i < k; i++) {
			int* val = int_new(t2[i]);
			vect_append(val, tab2);
		}

		/* Tri par ma fonction heap_sort*/
		avant = clock();
		heapsort(tab2);
		apres = clock();
		temps2 = ((double)apres - avant) / CLOCKS_PER_SEC;

		/* Tri par mergesort */
		vect_t tab3 = vect_new(k, int_fprintf, int_delete, int_equal);

		for (size_t i = 0; i < k; i++) {
			int* val = int_new(t3[i]);
			vect_append(val, tab3);
		}

		avant = clock();
		mergesort(tab3);
		apres = clock();
		temps3 = ((double)apres - avant) / CLOCKS_PER_SEC;

		/* Affichage des temps des 3 tris dans le fichier */
		if (fp) {
			fprintf(fp, "%d\t%lf\t%lf\t%lf\n", k, temps1, temps2, temps3);
		}
		printf("k = %d\tQuickSort Time = %lf\tHeapSort Time = %lf\tMergeSort Time = %lf\n", k, temps1, temps2, temps3);
		
		free(t1);
		free(t2);
		free(t3);
		vect_delete(tab1);
		vect_delete(tab2);
		vect_delete(tab3);
	}

	/* Affichage des 3 courbes contenues dans le fichier tempstri.dat avec le logiciel gnuplot */
	if (fp) {
		fclose(fp);
		system("gnuplot -p -e \"set logscale x; f(x) = a * x * log(x); fit f(x) 'tempstri.dat' u 1:2 via a;"
			"plot 'tempstri.dat' u 1:2 with line lt 4 title 'quickSort', a * x * log(x)  with line lt 6 title 'Fit quick',"
			"'tempstri.dat' u 1:3 with line lt 2 title 'MonTriHeap',"
			"'tempstri.dat' u 1:4 with line lt 1 title 'MergeSort'; quit\"");
	}
}