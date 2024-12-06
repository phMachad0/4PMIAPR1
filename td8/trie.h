#include <stdio.h>
#include <stdlib.h>

typedef
        struct _node {
	struct _node *sons[26];
} *tree_t;

tree_t trie_new();

tree_t trie_insert(char *word, tree_t t);

int trie_lookup(char *word, tree_t t);

void trie_delete(tree_t t);