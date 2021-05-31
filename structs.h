#include <stdlib.h>
#include "defs.h"

struct str_list
{
	size_t elements_amount;
	char *elements[MAX_LIST_LENGTH];
};

typedef struct str_list str_list;

typedef struct str_tree_node str_tree_node;

struct str_tree_node {
	char *label;
	size_t children_amount;
	str_tree_node *(children_ptrs[MAX_CHILDREN_AMOUNT]);
};

struct str_tree
{
	str_tree_node *root_ptr;
};
typedef struct str_tree str_tree;

struct question
{
	char *text;
	str_list *answers;
	size_t correct_index;
};
typedef struct question question;