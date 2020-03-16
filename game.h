#include <curses.h>

#define BLOCK '#'
char** board;
int h, w;

void start(WINDOW* win);
void populate(void);
int countn(int x, int y);
void apply(char** new_board);
