CC=gcc
CFLAGS=-W -I.

revmake: main.o str_list.o str_tree.o load_topics.o kevstr.o question.o game.o 
	$(CC) -Wall main.c str_list.c str_tree.c load_topics.c kevstr.c question.c game.c -o reversion