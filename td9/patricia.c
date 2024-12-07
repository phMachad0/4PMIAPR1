#include "patricia.h"

radix_t patricia_new(char *word) {
    radix_t tree;

    if ((tree=malloc(sizeof(*tree))) == NULL)
        return NULL;

    tree->value = strdup(word); 
    tree->sons = NULL;
    tree->brothers = NULL;
    
    return tree;
}

radix_t patricia_insert(char *word, radix_t t) {
    if (t == NULL) {
        t = patricia_new(word);
        return t;
    }

    while (t != NULL) {
        int i = 0;
        while (i < strlen(t->value) &&
               i < strlen(word) &&
               t->value[i] == word[i]) {
            i++;
        }

        if (i == 0) {
            if (t->brothers == NULL) {
                t->brothers = patricia_new(word);
            }
            t = t->brothers;
        } else if (i < strlen(t->value)) {
            radix_t new_son = patricia_new(t->value + i);
            new_son->sons = t->sons; 
            t->value[i] = '\0';
            t->sons = new_son;

            if (i < strlen(word)) {
                new_son->brothers = patricia_new(word + i);
            }
            return t;
        } else {
            word += i;
            if (*word == '\0') {
                return t;
            }
            if (t->sons == NULL) {
                t->sons = patricia_new(word);
            }
            t = t->sons;
        }
    }
    return t;
}

int patricia_lookup(char *word, radix_t t) {
    radix_t current = t;
    while (current != NULL) {
        int len = strlen(current->value);
        if (strncmp(current->value, word, len) == 0) {
            word += len;
            if (*word == '\0') {
                return 1; 
            }
            current = current->sons; 
        } else {
            current = current->brothers; 
        }
    }
    return 0; 
}

void patricia_delete(radix_t t) {
    if (t == NULL) {
        return;
    }

    if (t->sons != NULL) {
        printf("Deleting %s\n", t->value);
        patricia_delete(t->sons);
        // free(t->value);
    }

    if (t->brothers != NULL) {
        printf("Deleting %s\n", t->value);
        patricia_delete(t->brothers);
        // free(t->value);
    }

    // patricia_delete(t->sons);
    // patricia_delete(t->brothers);

    printf("Deleting %s\n", t->value);
    free(t->value);
    free(t);
}