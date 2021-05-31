#include "defs.h"
#include "structs.h"
#include "str_list.h"
#include "load_topics.h"
#include <time.h>
#include <stdio.h>
#include "str_tree.h"
#include "game.h"

int main(void)
{
	time_t t;
	srand((unsigned) time(&t));

	load_topics();
	return launch_single_lang_game_console();
}

