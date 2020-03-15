#include <curses.h>

#define BLOCK '#'
char** board;
int h, w;

void start(WINDOW* win);
void populate(WINDOW* win);
int countn(int x, int y);
void apply(WINDOW* win, char** new_board);
