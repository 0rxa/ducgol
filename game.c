// Any live cell with fewer than two live neighbours dies
// Any live cell with two or three live neighbours lives
// Any live cell with more than three live neighbours dies
// Any dead cell with exactly three live neighbours comes to life

#include "game.h"

#include <stdlib.h>
#include <string.h>

void
step(WINDOW* win)
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
	free(new_board);
}

void
import_template(FILE* template, WINDOW* win)
{
	getmaxyx(win, h, w);
	char** template_board = calloc((h+1), sizeof(char*));
	for(int c = 0; c <= h; c++)
	{
		template_board[c] = calloc((w+1), sizeof(char));
		for(int g = 0; g <= w; g++) template_board[c][g] = FIELD;

		for(int g = 0; g <= w; g++)
		{
			if(template == NULL) break;
			char ch = fgetc(template);

			if(ch == EOF)
			{
				fclose(template);
				template = NULL;
				break;
			}

			if(ch == '\n') break;

			if(ch != FIELD) template_board[c][g] = BLOCK;

			if(g+1 > w)
			{
				while(fgetc(template) != '\n');
				break;
			}
		}
	}

	apply(template_board);
	free(template_board);
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
			board[c][g] = mvinch(c, g);
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
