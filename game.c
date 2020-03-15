#include "game.h"
#include <stdlib.h>

void
start(WINDOW* win)
{
	populate(win);

	for(int c = 0; c <= h; c++)
	{
		for(int g = 0; g <= w; g++)
		{
			int neighbours = countn(g, c);
			char current = mvwinch(win, c, g);
			if(current == BLOCK && neighbours < 2 || neighbours > 3)
			{
				board[c][g] = ' ';
			}
			else if(current != BLOCK && neighbours == 3)
			{
				board[c][g] = BLOCK;
			}
		}
	}

	apply(win);
}

void
populate(WINDOW* win)
{
	getmaxyx(win, h, w);
	board = calloc((h+1), sizeof(char*));
	for(int c = 0; c <= h; c++)
	{
		board[c] = calloc((w+1), sizeof(char));
		for(int g = 0; g <= w; g++) board[c][g] = ' ';
	}

	for(int c = 0; c <= h; c++)
	{
		for(int g = 0; g <= w; g++)
		{
			char ch = mvwinch(win, c, g);
			ch = ch == BLOCK ? ch : ' ';
			board[c][g] = ch;
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

	for(int c = up; c <= down; c++)
	{
		for(int g = left; g <= right; g++)
		{
			if(g == x && c == y) continue;
			if(board[c][g] == BLOCK) neighbours++;
		}
	}

	return neighbours;
}

void
apply(WINDOW* win)
{
	for(int c = 0; c <= w; c++)
	{
		for(int g = 0; g <= h; g++)
		{
			mvwaddch(win, c, g, board[c][g]);
		}
	}
}
