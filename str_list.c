#include <stdio.h>
/**
 * @author Kevin Higgins
 * A basic list of strings that can be added to (though not yet shortened) and selected from at random
 * (initialisation of the RNG must have been previously done elsewhere, if desired)
 */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "defs.h"

int add_to_list(str_list *list_ptr, char *str)
{
	if (list_ptr->elements_amount == MAX_LIST_LENGTH)
	{
		return 1;
	}
	list_ptr->elements[list_ptr->elements_amount] = str;
	list_ptr->elements_amount++;
	return 0;
}

str_list *build_list(size_t str_amount, char **str_arr)
{
	str_list *list = calloc(1, sizeof(str_list));
	for (size_t i = 0; i < str_amount; i++)
	{
		if (add_to_list(list, str_arr[i])) exit(EXIT_FAILURE);
	}
	return list;
}

str_list * ptr_to_empty_list(void)
{
	str_list *list = calloc(1, sizeof(str_list));
	return list;
}


void debug_print_list(str_list *list)
{
	for (size_t i = 0; i < list->elements_amount; i++)
	{
		puts(list->elements[i]);
	}
}