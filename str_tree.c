#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include <string.h>
#include "str_list.h"
#include "str_tree.h"

str_tree_node *ptr_to_new_node_labelled(char *label);

str_tree *build_tree(char *label)
{
	str_tree *tree = calloc(1, sizeof(str_tree));

	tree->root_ptr = ptr_to_new_node_labelled(label);
	return tree;
}


str_tree_node *ptr_to_new_node_labelled(char *label)
{
	str_tree_node *root = calloc(1, sizeof(root));
	root->label = label;
	return root;
}
str_tree_node *get_child_ptr_by_label(str_tree_node *parent_ptr, char *label)
{
	// assumes that siblings won't have same label - this was considered in the design stage
	for (size_t i = 0; i < parent_ptr->children_amount; i++)
	{
		if (!strcmp(parent_ptr->children_ptrs[i]->label, label))
		{
			return parent_ptr->children_ptrs[i];
		}
	}
	return NULL;
}

str_tree_node *get_node_by_key(str_tree *tree, str_list *key_ptr)
{
	size_t levels = key_ptr->elements_amount;
	str_tree_node *curr = tree->root_ptr;
	for(size_t i = 0; i < levels; i++)
	{
		curr = get_child_ptr_by_label(curr, key_ptr->elements[i]);
		if (!curr) 
		{
			puts("Returning NULL as the following key did not point to any node:");
			debug_print_list(key_ptr);
			return NULL;
		}
	}
	return curr;
}
str_list *get_ptr_to_childrens_labels(str_tree_node *parent_ptr)
{
	str_list *list = ptr_to_empty_list();
	for (size_t i = 0; i < parent_ptr->children_amount; i++)
	{

		if (add_to_list(list, parent_ptr->children_ptrs[i]->label)) exit(EXIT_FAILURE);
	}
	return list;
}


int add_new_child_labelled(str_tree_node *parent_ptr, char *label)
{
	if (parent_ptr->children_amount == MAX_CHILDREN_AMOUNT)
	{
		return 1;
	}

	parent_ptr->children_ptrs[parent_ptr->children_amount++] = ptr_to_new_node_labelled(label);
	return 0;
}