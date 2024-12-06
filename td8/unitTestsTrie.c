#include <stdio.h>
#include "trie.h"

int main() {
    tree_t t = trie_new();
    if (t != NULL) {
        printf("trie_new() test passed.\n");
    } else {
        printf("trie_new() test failed.\n");
    }

    t = trie_insert("hello", t);
    if (t != NULL) {
        printf("trie_insert() test passed.\n");
    } else {
        printf("trie_insert() test failed.\n");
    }
    t = trie_insert("world", t);
    t = trie_insert("github", t);
    if (trie_lookup("hello", t) && trie_lookup("world", t) && trie_lookup("github", t)) {
        printf("trie_insert() and trie_lookup() tests passed.\n");
    } else {
        printf("trie_insert() and trie_lookup() tests failed.\n");
    }

    if (trie_lookup("hell", t) == 0) {
        printf("trie_lookup() test passed.\n");
    } else {
        printf("trie_lookup() test failed.\n");
    }
    
    trie_delete(t);

    return 0;
}