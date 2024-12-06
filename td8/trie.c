#include "trie.h"

tree_t trie_new() {
    tree_t tree;

    if ((tree=malloc(sizeof(*tree))) == NULL)
        return NULL;

    for (int i = 0; i < 26; i++) {
        tree->sons[i] = NULL;
    }
    
    return tree;
}

tree_t trie_insert(char *word, tree_t t) {
    if (t == NULL) {
        t = trie_new();
    }

    if (*word == '\0') {
        return t;
    }

    for (int i = 0; i < 26; i++) {
        if (*word == 'a' + i) {
            t->sons[i] = trie_insert(word + 1, t->sons[i]);
        }
    }

    return t;
}


int trie_lookup(char *word, tree_t t) {
    if (t == NULL) {
        return 0;
    }

    if (*word == '\0') {
        return 1;
    }

    int next = *word - 'a';
    return trie_lookup(word + 1, (tree_t)(t->sons + next));
}

void trie_delete(tree_t t) {
    if (t == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (t->sons[i] != NULL) {
            trie_delete(t->sons[i]);
        }
    }

    free(t);
}