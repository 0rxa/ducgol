#include "game.h"

#include <stdlib.h>
#include <string.h>

void
start(WINDOW* win)
{
	getmaxyx(win, h, w);
	populate();
	char** new_board = calloc((h+1), sizeof(char*));
	for(int c = 0; c <= h; c++)
	{
		new_board[c] = calloc((w+1), sizeof(char));
		memcpy(new_board[c], board[c], w+1);
		for(int g = 0; g <= w; g++)
		{
			int neighbours = countn(g, c);
			char current = mvinch(c, g);
			if(current == BLOCK && neighbours < 2 || neighbours > 3)
			{
				new_board[c][g] = FIELD;
			}
			else if(current != BLOCK && neighbours == 3)
			{
				new_board[c][g] = BLOCK;
			}
		}
	}

	apply(new_board);
}

void
populate()
{
	board = calloc((h+1), sizeof(char*));
	for(int c = 0; c <= h; c++)
	{
		board[c] = calloc((w+1), sizeof(char));
		for(int g = 0; g <= w; g++)
		{
			char ch = mvinch(c, g);
			ch = ch == BLOCK ? ch : FIELD;
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
apply(char** new_board)
{
	for(int c = 0; c <= h; c++)
	{
		for(int g = 0; g <= w; g++)
		{
			mvaddch(c, g, new_board[c][g]);
		}
	}
}
