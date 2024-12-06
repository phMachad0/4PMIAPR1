#include "hashvset.h"

hashvset_t hashvset_new(int n, unsigned int (*fhachage)(void * ), void (*print_key)(void*,FILE*), void* (*delete_key)(
				void*),int (*compare_key)(void* e1, void* e2) ) {

	hashvset_t table;

	if ((table=malloc(sizeof(*table))) == NULL)
		return NULL;

	if ((table->data=calloc(n,sizeof(*(table->data)))) == NULL) {
		free(table);
		return NULL;
	}

    for(int i = 0; i < n; i++) {
        table->data[i].busy = EMPTY;
    }

	table->total_number = 0;
	table->size = n;
	table->hachage = fhachage;
	table->delete_key = delete_key;
	table->compare_key = compare_key;
	table->print_key = print_key;

	return table;
}

hashvset_t hashvset_delete(hashvset_t table) {
	if (table==NULL) return NULL;
	for (unsigned int i = 0; i < table->size; i++) {
        if (table->data[i].busy == OCCUPED)
            table->delete_key(table->data[i].key);
		table->data[i].busy = EMPTY;
	}
    free(table->data);
	table->total_number = 0;
	return table;
}

int hashvset_put(void* key, hashvset_t table) {
	int i = 0;
	
	for (i = 0; i < table->size;) {
		int h = table->hachage(key);
		int slot = (h + i*i) % table->size;

		if (table->data[slot].busy == FREE || table->data[slot].busy == EMPTY) {
			table->data[slot].key = key;
            table->data[slot].busy = OCCUPED;
			return 1;
		} else {
            if (table->data[slot].busy == OCCUPED && table->compare_key(table->data[slot].key, key) == 1) {
				return 1;
			} else {
                i++;
            }
		}
	}

	// hashvset_new_length(1, table);
	// hashvset_put(key, table);
    return 0;
}

int hashvset_find_key(void* key, hashvset_t table) {
	int i = 0;

	for (i = 0; i < table->size;) {
		int h = table->hachage(key);
		int slot = (h + i*i) % table->size;

		if (table->data[slot].busy == OCCUPED) {
			if (table->compare_key(table->data[slot].key, key) == 1) {
				return slot;
			} else {
                i++;
            }
		} else {
            return -1;
        }
	}
    return -1;
}
int hashvset_remove_key(void* key, hashvset_t table) {
    int slot = hashvset_find_key(key, table);
    if (slot != -1) {
        table->data[slot].busy = FREE;
        return 1;
    }
}
void hashvset_printf(hashvset_t table) {
    for (int i = 0; i < table->size; i++) {
        if (table->data[i].busy == OCCUPED) {
            table->print_key(table->data[i].key, stdout);
        }
    }
}
void hashvset_fprintf(hashvset_t t,FILE*fp) {
    for (int i = 0; i < t->size; i++) {
        if (t->data[i].busy == OCCUPED) {
			fprintf(fp, "[%d]: ", i);
            t->print_key(t->data[i].key, fp);
        }
    }
    fprintf(fp, "\n");
}
// sens =1 pour accroitre la table, -1 sinon
int hashvset_new_length(int sens, hashvset_t table) {
    if (sens == 1) {
        table->size *= 2;
    	table->data = realloc(table->data, table->size*sizeof(*(table->data)));

		for (unsigned int i = table->size/2; i < table->size; i++) {
			table->data[i].busy = EMPTY;
		}

    } else {
        table->size /= 2;
    	table->data = realloc(table->data, table->size*sizeof(*(table->data)));
    }



	printf("Table size: %d\n", table->size);
    return 1;
}