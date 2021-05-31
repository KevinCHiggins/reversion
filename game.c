#include "structs.h"
#include "load_topics.h"
#include "enum.h"
#include "str_list.h"
#include "kevstr.h"
#include "question.h"
#include <string.h>
#include <stdio.h>
question_type get_random_question_type(void);
question *make_random_question(char *lang);
char *choose_from_list_console(str_list *list);
char *select_language_console(void);
int play_single_lang_game_console(char *lang);
int question_structs_are_equal(question *q1, question *q2);
size_t which_slot_holds(size_t *counts, size_t n);
question *make_array_of_random_questions(char * lang);

int launch_single_lang_game_console()
{
	puts("Welcome to Re: Version. Enter 'q' or 'Q' to quit at any time.");

	puts("Which language do you wish to be tested on?");
	char *lang = choose_from_list_console(get_languages());

	printf("Prepare yourself for %lu questions on %s!\n", (size_t) QS_PER_GAME, lang); // see this SO point https://stackoverflow.com/questions/13162528/what-is-the-datatype-of-a-defined-constant
	size_t correct_amount = 0;
	size_t questions_asked = 0;
	question *q_arr = make_array_of_random_questions(lang);
	while (questions_asked < QS_PER_GAME)
	{
		question *q = q_arr + questions_asked;
		printf("Q%lu. %s\n", ++questions_asked, q->text);
		if (!strcmp(choose_from_list_console(q->answers), q->answers->elements[q->correct_index]))
		{
			puts("Correct!");
			correct_amount++;
		}
		else
		{
			puts(ks_cat("Wrong! The correct answer was ", q->answers->elements[q->correct_index]));
		}
	}
	printf("You got %lu out of %lu correct!\n", correct_amount, questions_asked);
	return 0;
}


// for the moment, I'm going for the number keys, one-
// indexed. This is why I've limited the list and children amounts in defs.h to 9.
char *choose_from_list_console(str_list *list)
{
	for (size_t i = 0; i < list->elements_amount; i++)
	{
		printf("%lu. %s\n", i + 1, list->elements[i]); // one-indexed is my preference
	}

	char inp = getchar();
	size_t selection_one_indexed = 0; // so, zero flags "no valid input received yet"
	while (!selection_one_indexed)
	{
		// test if in numerical range (not including zero as one-indexed)
		// ladder of ifs!
		if (inp > '0' && inp <= '9')
		{
			selection_one_indexed = inp - '0';
		}
		else if (inp == '\n')
		{
			inp = getchar();
		}
		else if (inp == 'q' || inp == 'Q')
		{
			exit(0);
		}
		else
		{
			puts("Please enter a digit to make a selection, or 'q' or 'Q' to quit.");
		}
	}
	return list->elements[selection_one_indexed - 1];
}

// we'll add bitfield for question types later
question *make_random_question(char *lang)
{
	question *q = calloc(1, sizeof(question));
	switch(get_random_question_type())
	{
		case INTRODUCED_IN_WHICH:
		{
			size_t total = count_features_of_lang(lang);
			size_t selection = rand() % total;
			size_t *feature_counts_per_version = count_features_of_lang_per_version(lang);
			size_t correct = which_slot_holds(feature_counts_per_version, selection);
			str_list *answer_labels = get_versions(lang);
			if (answer_labels == NULL) puts("Null pointer.");
			q->answers = answer_labels;
			char *text = ks_cat("In which version of ", lang);
			char *feat_label = get_nth_feature_of_lang(lang, selection);
			if (ks_is_plural(feat_label)) text = ks_cat(text, " were "); else text = ks_cat(text, " was ");
			text = ks_cat(text, feat_label);
			text = ks_cat(text, " introduced?");
			q->text = text;
			q->correct_index = correct;
			return q;
		}
		default: {}
	}
	return q;
}

question *make_array_of_random_questions(char * lang)
{
	question *arr = malloc(sizeof(question) * QS_PER_GAME);
	// iterate through question array, filling it with unique questions
	for (size_t i = 0; i < QS_PER_GAME; i++)
	{
		question candidate_q;
		while (1)
		{
			candidate_q = *make_random_question(lang);
			//printf("Checking q %s for pos %lu", candidate_q.text, i);
			int no_duplicates = 1;
			for (size_t j = 0; j < i; j++)
			{
				no_duplicates = 1;
				if (!question_structs_are_different(&arr[j], &candidate_q))
				{
					no_duplicates = 0;
					break;
				}

			}
			if (no_duplicates) 
			{
				break;
			}
		}
		arr[i] = candidate_q;
		
	}
	return arr;
}



// assumes n is in one slot, otherwise, unsafe
size_t which_slot_holds(size_t *counts, size_t n)
{
	size_t curr_slot = 0;

	for (; ; curr_slot++)
	{
		// if it's in the current version
		if (n < counts[curr_slot])
		{
			return curr_slot;
		}
		else // subtract current versions' features amount from n so as to reduce it to an offset into all features of subsequent versions
		{
			n-= counts[curr_slot];
		}
	}

	return -1;	
}

question_type get_random_question_type()
{
	return INTRODUCED_IN_WHICH;
}

// like other functions in game.c, this depends on str_list and load_topics, so
// I think it belongs here rather than in str_list (as the randomness is a
// gameplay rule, not an aspect of the data structure)
char *get_random_string_from_list(str_list *list)
{
	size_t i = rand() % list->elements_amount;
	return(list->elements[i]);
}
