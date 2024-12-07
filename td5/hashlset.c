#include <stdio.h>
#include "hashlset.h"

hashlset_t hashlset_new(int n, unsigned int (*fhachage)(void*), void (*print_key)(void*,FILE*), void* (*delete_key)(
				void*), int (*compare_key)(void* e1, void* e2)) {
	hashlset_t table;

	if ((table=malloc(sizeof(*table))) == NULL)
		return NULL;

	if ((table->data=calloc(n,sizeof(*(table->data)))) == NULL) {
		free(table);
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		table->data[i] = list_new(print_key,delete_key,compare_key);
	}

	table->total_number = 0;
	table->size = n;
	table->hachage = fhachage;
	table->delete_key = delete_key;
	table->compare_key = compare_key;
	table->print_key = print_key;

	return table;
}

hashlset_t hashlset_delete(hashlset_t table) {
	if (table==NULL) return NULL;
	for (unsigned int i = 0; i < table->size; i++) {
		table->data[i] = list_delete(table->data[i]);
		free(table->data[i]);
	}
	table->total_number = 0;
	free(table->data);
	return table;
}

int hashlset_put(void* key, hashlset_t table) {
	int h = table->hachage(key);
	int slot = h % table->size;

	if (list_lookup(key, table->data[slot], table->compare_key) != NULL) {
		return 1;
	}

	if (list_add_first(key, table->data[slot])) {
		table->total_number++;
		return 1;
	} else {
		return 0;
	}
}

int hashlset_find_key(void* key, hashlset_t table) {
	int h = table->hachage(key);
	int slot = h % table->size;

	if (list_lookup(key, table->data[slot], table->compare_key) != NULL) {
		return 1;
	} else {
		return 0;
	}
}

int hashlset_remove_key(void* key, hashlset_t table) {
	int h = table->hachage(key);
	int slot = h % table->size;

	if (list_lookup(key, table->data[slot], table->compare_key) != NULL) {
		table->data[slot] = list_remove(key, table->data[slot]);
		table->total_number--;
		return 1;
	} else {
		return 0;
	}
}

void hashlset_fprintf(hashlset_t table, FILE*fp) {
	printf("--------------------\n");
	for (unsigned int i = 0; i < table->size; i++) {
		printf("Slot %d : ", i);
		list_printf(table->data[i]);
	}
	printf("--------------------\n");
}

double hashlset_memory_usage(hashlset_t table) {
    double total_memory = 0;
    total_memory += sizeof(*table);

    total_memory += table->size * sizeof(list_t *);

    for (unsigned int i = 0; i < table->size; i++) {
        total_memory += list_memory_usage(table->data[i]);
    }

    return total_memory / 1024 / 1024;
}