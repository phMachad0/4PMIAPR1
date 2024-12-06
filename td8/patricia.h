#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef
        struct node_radix {
	char* value;
	struct node_radix *sons, * brothers;
}  *radix_t;

radix_t patricia_new();

radix_t patricia_insert(char *word, radix_t t);

int patricia_lookup(char *word, radix_t t);

void patricia_delete(radix_t t);