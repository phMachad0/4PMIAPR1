#include <stdio.h>
#include "heap.h"
#include "../td4/double.h"

int main() {
	heap_t tas = heap_new(10, double_fprintf, double_delete, double_equal);

	printf("Ajout de 10,20,30,40,50,60,70 : \n");
	heap_add(double_new(11),tas);
	heap_add(double_new(3),tas);
    heap_add(double_new(2),tas);
    heap_add(double_new(1),tas);
	heap_add(double_new(15),tas);
	heap_add(double_new(5),tas);
	heap_add(double_new(4),tas);
	heap_add(double_new(45),tas);

	heap_fprintf(tas, stdout);
	printf("Extrema: %lf\n", *(double*)heap_get_extrema(tas));

	printf("Heap verification: %d\n", heap_verification(tas));
    
	while (!heap_is_empty(tas)) {
		printf("Deleting extrema: %d\n", *(int*)heap_get_extrema(tas));
		heap_delete_extrema(tas);
	}


	tas = heap_delete(tas);

	return 0;
}