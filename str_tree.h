str_tree *build_tree(char *label);

str_tree_node *get_child_ptr_by_label(str_tree_node *parent_ptr, char *label);

int add_new_child_labelled(str_tree_node *parent_ptr, char *label);

str_list *get_ptr_to_childrens_labels(str_tree_node *parent_ptr);

str_tree_node *get_node_by_key(str_tree *tree, str_list *key_ptr);
