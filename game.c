#include "game.h"
#include <stdlib.h>

char** board;
int h, w;

void
start(WINDOW* win)
{
	populate(win);

	for(int c = 0; c <= h; c++)
	{
		for(int g = 0; g <= w; g++)
		{
			int neighbours = countn(g, c);
		}
	}
}

void
populate(WINDOW* win)
{
	getmaxyx(win, h, w);
	board = calloc(((h+1)*(w+1)), sizeof(char));

	for(int c = 0; c <= h; c++)
	{
		for(int g = 0; g <= w; g++)
		{
			board[c][g] = winch(win);
		}
	}
}

int
countn(int x, int y)
{
	int neighbours = 0;
	int left  = x>0 ? x-1 : 0;
	int right = x<w ? x+1 : w;
	int up    = y>0 ? y-1 : 0;
	int down  = y<h ? y+1 : h;

	for(int c = left; c <= right; c++)
	{
		for(int g = up; g <= down; g++)
		{
			if(g == x && c == y) continue;
			if(board[c][g] == '#') neighbours++;
		}
	}

	return neighbours;
}
