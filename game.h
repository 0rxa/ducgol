#include <curses.h>
#include <stdlib.h>

#define BLOCK '#'
#define FIELD ' '

typedef struct config {
	int help;
	int interactive;
	char* path;
	time_t sleep;
} config;

void step(WINDOW* win);
void populate(void);
int countn(int x, int y);
void apply(char** new_board);
void import_template(FILE* template, WINDOW* win);
