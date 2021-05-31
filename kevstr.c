#include "kevstr.h"
#include <stdlib.h>
#include <string.h>


char *ks_cat(char *s1, char *s2)
{
	size_t len1 = strlen(s1);
	size_t len = len1 + strlen(s2);
	char *cat = malloc(len * sizeof(char) + 1);
	size_t i = 0;
	for (; s1[i]; i++)
	{
		cat[i] = s1[i];
	}
	for (; s2[i - len1]; i++)
	{	
		cat[i] = s2[i - len1];
	}
	cat[i] = 0;
	return cat;
}

// just a very rough one to start us off!
int ks_is_plural(char *s)
{
	size_t len = strlen(s);
	if (s[len - 1] == 's') return 1; else return 0;
}