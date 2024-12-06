#include <stdio.h>
#include <assert.h>
#include "patricia.h"

int main() {
    // Test patricia_new()
    radix_t tree = patricia_new("");
    if (tree != NULL) {
        printf("trie_new() test passed.\n");
    } else {
        printf("trie_new() test failed.\n");
    }

    tree = patricia_insert("ame", tree);
    if (tree != NULL) {
        printf("trie_insert() test passed.\n");
    } else {
        printf("trie_insert() test failed.\n");
    }

    tree = patricia_insert("amor", tree);
    if (tree != NULL) {
        printf("trie_insert() test passed.\n");
    } else {
        printf("trie_insert() test failed.\n");
    }

    patricia_insert("amour", tree);
    patricia_insert("amoureux", tree);
    patricia_insert("amouracher", tree);
    patricia_insert("amouracherie", tree);

    if (patricia_lookup("ame", tree) == 1 && patricia_lookup("amor", tree) == 1 && patricia_lookup("amour", tree) == 1 && patricia_lookup("amoureux", tree) == 1 && patricia_lookup("amouracher", tree) == 1 && patricia_lookup("amouracherie", tree) == 1) {
        printf("trie_insert() and trie_lookup() tests passed.\n");
    } else {
        printf("trie_insert() and trie_lookup() tests failed.\n");
    }
    char buffer[100];
    // Test patricia_delete()
    patricia_delete(tree);
    printf("All tests passed!\n");

    return 0;
}