#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "patricia.h"

patricia_tree_t patricia_new(char *word) {
	patricia_tree_t tree;

	if ((tree=malloc(sizeof(*tree))) == NULL)
		return NULL;

	tree->value = strdup(word);
	tree->sons = NULL;
	tree->brothers = NULL;

	return tree;
}

patricia_tree_t patricia_insert(char *word, patricia_tree_t tree) {

	if (tree == NULL) {
		tree = patricia_new(word);
	}
    
	if (*word == '\0' || tree->value[0] == word[0]) {
		if (*word == '\0') {
			if (tree->sons == NULL) {
				tree->sons = patricia_new("\0");
			}
		} else {
			int sameChars=0;
			for (int i=0; word[i] != '\0' && tree->value[i] != '\0'; i++) {
				if (word[i] == tree->value[i]) sameChars++;
			}

			tree->sons = patricia_insert(word + sameChars, tree->sons);
		}
	} else {
		tree->brothers = patricia_insert(word, tree->brothers);
	}

	return tree;
}

int patricia_lookup(char *word, patricia_tree_t tree) {
    while (tree != NULL) {
        *word = tolower(*word);
        if (*word == '\0' && tree->value[0] == '\0') {
            return 1;
        }

        if (tree->value[0] == *word || (tree->value[0] == '\0' && *word == '\0')) {
            int sameChars=0;
            for (int i=0; word[i] != '\0' && tree->value[i] != '\0'; i++) {
                if (word[i] == tree->value[i]) sameChars++;
            }

            word += sameChars;
            tree = tree->sons;
        } else {
            tree = tree->brothers;
        }
    }
    return 0;
}

void patricia_delete(patricia_tree_t tree)
{
	if (tree!=NULL) {
		patricia_delete(tree->brothers);
		patricia_delete(tree->sons);
		if (tree->value != NULL) {
			free(tree->value);
		}
		free(tree);
	}
}

size_t patricia_memory_size (patricia_tree_t tree) {
	if (tree == NULL) {
		return 0;
	}

	size_t size = (double) sizeof(*tree);
	if (tree->value != NULL) {
		size += strlen(tree->value) + 1;
	}

	if (tree->sons != NULL) {
		size += patricia_memory_size(tree->sons);
	}

	if (tree->brothers != NULL) {
		size += patricia_memory_size(tree->brothers);
	}

	return size;
}

double patricia_memory_usage(patricia_tree_t tree) {
	return (double) patricia_memory_size(tree) / 1024.0 / 1024.0;
}