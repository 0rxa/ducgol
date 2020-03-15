// Any live cell with fewer than two live neighbours dies
// Any live cell with two or three live neighbours lives
// Any live cell with more than three live neighbours dies
// Any dead cell with exactly three live neighbours comes to life

#include "./game.h"

#define BLOCK '#'

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int x = 0, y = 0;
	int run = 0;
	int ch;
	while(1)
	{
		if(run) start(stdscr);
		int h, w;
		getmaxyx(stdscr, h, w);
		ch = getch();

		if( ch == ' ' )
		{
			char c = inch() == BLOCK ? ' ' : BLOCK;
			mvaddch(y, x, c);
			x++;
		}
		else if(ch == KEY_LEFT  && x-1 >= 0) x--;
		else if(ch == KEY_RIGHT && x+1 <= w) x++;
		else if(ch == KEY_DOWN  && y+1 <= h) y++;
		else if(ch == KEY_UP    && y-1 >= 0) y--;
		else if(ch == '\x0A') run = !run;
		move(y, x);
		refresh();
	}

	endwin();
}