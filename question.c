#include <string.h>
#include <stdio.h>
#include "structs.h"
int question_structs_are_different(question *q1, question *q2)
{
	// comparing the texts means that the same feature could be quizzed
	// in a different question type and not be flagged here as equal
	// which is fine - it's the exact repetition of topic and question type
	// that's annoying
	int are_equal = strcmp(q1->text, q2->text);
	//printf("Question\t'%s' \nand question \t'%s'\n yield %d", q1->text, q2->text, are_equal);
	return are_equal;
}