#include <stdio.h>
#include "structs.h"
#include "str_tree.h"
#include "str_list.h"
#include "load_topics.h"

// this file wraps the data structure and also fills it with data
// while these two things could be separated, they both require knowledge of the data structure
// so it makes sense to encapsulate that in here
// it provides an API for the game logic, in topic-specific terms

// internal convenience functions
str_list *build_lang_key(char *lang); 
str_list *build_ver_key(char *lang, char *ver);
str_list *build_feat_key(char *lang, char *ver, char *feat);

str_tree *tree_ptr;

// note that insertions of versions must be IN CHRONOLOGICAL ORDER so we can build date-based questions
void load_topics(void)
{
	tree_ptr = build_tree("topics");
	add_new_child_labelled(tree_ptr->root_ptr, "C");
	str_tree_node *working_ptr = get_node_by_key(tree_ptr, build_lang_key("C"));
	add_new_child_labelled(working_ptr, "K&R");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("C", "K&R"));

	add_new_child_labelled(working_ptr, "long int");
	add_new_child_labelled(working_ptr, "unsigned int");
	add_new_child_labelled(working_ptr, "compound operators");
	add_new_child_labelled(working_ptr, "standard I/O library");

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("C"));
	add_new_child_labelled(working_ptr, "C89");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("C", "C89"));
	add_new_child_labelled(working_ptr, "void functions");
	add_new_child_labelled(working_ptr, "functions returning structs and unions");
	add_new_child_labelled(working_ptr, "enums");
	add_new_child_labelled(working_ptr, "assignment of structs");

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("C"));
	add_new_child_labelled(working_ptr, "C95");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("C", "C95"));
	add_new_child_labelled(working_ptr, "digraphs");
	add_new_child_labelled(working_ptr, "wide and multi-byte characters");
	add_new_child_labelled(working_ptr, "standard macros for operators");	

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("C"));
	add_new_child_labelled(working_ptr, "C99");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("C", "C99"));
	add_new_child_labelled(working_ptr, "long long, _Bool, _Complex, and _Imaginary types");
	add_new_child_labelled(working_ptr, "variable-length arrays");
	add_new_child_labelled(working_ptr, "flexible array members");
	add_new_child_labelled(working_ptr, "IEEE 754 floating point");
	add_new_child_labelled(working_ptr, "variadic macros");
	add_new_child_labelled(working_ptr, "inline functions");
	add_new_child_labelled(working_ptr, "one-line comments");
	add_new_child_labelled(working_ptr, "compulsory function types");

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("C"));
	add_new_child_labelled(working_ptr, "C11");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("C", "C11"));
	add_new_child_labelled(working_ptr, "type-generic macros");
	add_new_child_labelled(working_ptr, "anonymous structs");
	add_new_child_labelled(working_ptr, "atomic operations");
	add_new_child_labelled(working_ptr, "multi-threading");
	add_new_child_labelled(working_ptr, "bounds-checked functions");

	add_new_child_labelled(tree_ptr->root_ptr, "JavaScript");

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("JavaScript"));
	add_new_child_labelled(working_ptr, "ES3");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("JavaScript", "ES3"));
	add_new_child_labelled(working_ptr, "strict equality");
	add_new_child_labelled(working_ptr, "regular expression literals");
	add_new_child_labelled(working_ptr, "RegExp objects");
	add_new_child_labelled(working_ptr, "switch statement");
	add_new_child_labelled(working_ptr, "try/catch");

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("JavaScript"));
	add_new_child_labelled(working_ptr, "ES5");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("JavaScript", "ES5"));
	add_new_child_labelled(working_ptr, "new array methods");
	add_new_child_labelled(working_ptr, "use strict");
	add_new_child_labelled(working_ptr, "JSON");
	add_new_child_labelled(working_ptr, "Date methods");
	add_new_child_labelled(working_ptr, "getters and setters");

	working_ptr = get_node_by_key(tree_ptr, build_lang_key("JavaScript"));
	add_new_child_labelled(working_ptr, "ES6");
	working_ptr = get_node_by_key(tree_ptr, build_ver_key("JavaScript", "ES6"));
	add_new_child_labelled(working_ptr, "Babel");
	add_new_child_labelled(working_ptr, "fat arrow, implicit return, automatic binding to 'this'");
	add_new_child_labelled(working_ptr, "classes");
	add_new_child_labelled(working_ptr, "let and const statements");
	add_new_child_labelled(working_ptr, "destructuring");
	add_new_child_labelled(working_ptr, "rest and spread operators");
	add_new_child_labelled(working_ptr, "template literals");	


}
int contains_lang(char *lang)
{
	str_list *key_ptr = build_lang_key(lang);
	if (get_node_by_key(tree_ptr, key_ptr)) return 1; else return 0;
}
str_list *get_languages(void)
{
	return get_ptr_to_childrens_labels(tree_ptr->root_ptr);
}
str_list *get_versions(char *lang)
{
	str_list *key_ptr = build_lang_key(lang);
	return get_ptr_to_childrens_labels(get_node_by_key(tree_ptr, key_ptr));
}
str_list *get_features(char *lang, char *ver)
{
	str_list *key_ptr = build_ver_key(lang, ver);
	return get_ptr_to_childrens_labels(get_node_by_key(tree_ptr, key_ptr));
}


// we can imagine more complex stuff where a subset of versions is tested
// but I'll keep it basic for now
size_t count_features_of_lang(char *lang)
{
	size_t count = 0;
	str_tree_node *lang_ptr = get_node_by_key(tree_ptr, build_lang_key(lang));
	// iterate through the language's versions (children of its node)
	for (size_t i = 0; i < lang_ptr->children_amount; i++)
	{
		// for each version (child node) add its amount of children to the count
		count+= lang_ptr->children_ptrs[i]->children_amount;
	}
	return count;
}

size_t *count_features_of_lang_per_version(char *lang)
{
	
	static size_t counts[MAX_CHILDREN_AMOUNT] = {0}; // zero initialise
	str_tree_node *lang_ptr = get_node_by_key(tree_ptr, build_lang_key(lang));
	// iterate through the language's versions (children of its node)
	for (size_t i = 0; i < lang_ptr->children_amount; i++)
	{
		// for each version (child node) save its amount of children in the array
		counts[i] = lang_ptr->children_ptrs[i]->children_amount;
	}
	return counts;	
}

char *get_nth_feature_of_lang(char *lang, size_t n)
{
	//size_t *amount_per_version = count_features_of_lang_per_version(lang);
	
	size_t curr_ver = 0;
	str_tree_node *lang_ptr = get_node_by_key(tree_ptr, build_lang_key(lang));
	size_t ver_amount = lang_ptr->children_amount;
	// tick through versions of language to find nth feature
	for (; curr_ver < ver_amount; curr_ver++)
	{
		// if it's in the current version
		if (n < lang_ptr->children_ptrs[curr_ver]->children_amount)
		{
			return lang_ptr->children_ptrs[curr_ver]->children_ptrs[n]->label;
		}
		else // subtract current versions' features amount from n so as to reduce it to an offset into all features of subsequent versions
		{
			n-= lang_ptr->children_ptrs[curr_ver]->children_amount;
		}
	}
	return NULL;
}
// this functionality is in game.c
/*
size_t get_ver_num_containing_nth_of_all_features(char *lang, size_t n)
{
	//size_t *amount_per_version = count_features_of_lang_per_version(lang);
	size_t curr_ver = 0;
	str_tree_node *lang_ptr = get_node_by_key(tree_ptr, build_lang_key(lang));
	size_t ver_amount = lang_ptr->children_amount;
	// tick through versions of language to find nth feature
	for (; curr_ver < ver_amount; curr_ver++)
	{
		// if it's in the current version
		if (n < lang_ptr->children_ptrs[curr_ver]->children_amount)
		{
			return curr_ver;
		}
		else // subtract current versions' features amount from n so as to reduce it to an offset into all features of subsequent versions
		{
			n-= lang_ptr->children_ptrs[curr_ver]->children_amount;
		}
	}
	return -1;	
}
*/
// topic-specific convenience one-liners for making keys
str_list *build_lang_key(char *lang)
{
	str_list *list = ptr_to_empty_list();
	add_to_list(list, lang);
	return list;
}
str_list *build_ver_key(char *lang, char *ver)
{
	str_list *list = ptr_to_empty_list();
	add_to_list(list, lang);
	add_to_list(list, ver);
	return list;
}
str_list *build_feat_key(char *lang, char *ver, char *feat)
{
	str_list *list = ptr_to_empty_list();
	add_to_list(list, lang);
	add_to_list(list, ver);
	add_to_list(list, feat);
	return list;
}