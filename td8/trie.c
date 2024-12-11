#include "trie.h"
#include <ctype.h>
#include <stdlib.h>
#include "../projet/utils.h"

tree_t trie_new() {
	tree_t tree;

	if ((tree = malloc(sizeof(*tree))) == NULL)
		return NULL;

	for (int i = 0; i < 26; i++) {
		tree->sons[i] = NULL;
	}
	tree->is_terminal = 0;

	return tree;
}

tree_t trie_insert(char *word, tree_t t) {
	*word = tolower(*word);
	if (t == NULL) {
		t = trie_new();
	}

	if (*word == '\0') {
		t->is_terminal = 1;
		return t;
	}

	if (isalpha(*word)) {
		int index = *word - 'a';
		if (index >= 0 && index < 26) {
			t->sons[index] = trie_insert(word + 1, t->sons[index]);
		}
	}

	return t;
}

int trie_lookup(char *word, tree_t t) {
	*word = tolower(*word);
	if (t == NULL) {
		return 0;
	}

	if (*word == '\0') {
		return t->is_terminal;
	}

	if (isalpha(*word)) {
		int next = *word - 'a';
		if (next >= 0 && next < 26) {
			return trie_lookup(word + 1, t->sons[next]);
		}
	}
	return 0;
}

tree_t trie_delete(tree_t t) {
	if (t == NULL) {
		return t;
	}

	for (int i = 0; i < 26; i++) {
		if (t->sons[i] != NULL) {
			trie_delete(t->sons[i]);
		}
	}

	free(t);
	return NULL;
}

size_t trie_memory_size(tree_t tree) {
	if (tree == NULL) {
		return 0;
	}

	size_t size = sizeof(*tree);
	for (int i = 0; i < 26; i++) {
		size += trie_memory_size(tree->sons[i]);
	}

	return size;
}
double trie_memory_usage(tree_t tree) {
	if (tree == NULL) {
		return 0;
	}

	double size = sizeof(*tree);
	for (int i = 0; i < 26; ++i) {
		size += trie_memory_size(tree->sons[i]);
	}

	return size / 1024 / 1024;
}