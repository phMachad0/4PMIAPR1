#include <stdio.h>
#include <stdlib.h>

typedef
        struct _node {
	struct _node *sons[26];
        int is_terminal;
} *tree_t;

tree_t trie_new();

tree_t trie_insert(char *word, tree_t t);

int trie_lookup(char *word, tree_t t);

tree_t trie_delete(tree_t t);

double trie_memory_usage(tree_t tree);