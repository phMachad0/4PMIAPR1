typedef
        struct node_radix {
	char* value;
	struct node_radix *sons, * brothers;
}  *patricia_tree_t;

patricia_tree_t patricia_new(char *word);

patricia_tree_t patricia_insert(char *word, patricia_tree_t tree);
int patricia_lookup(char *word, patricia_tree_t tree);
void patricia_delete(patricia_tree_t tree);

double patricia_memory_usage(patricia_tree_t tree);
