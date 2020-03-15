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
	nodelay(stdscr, 1);
	noecho();
	keypad(stdscr, TRUE);

	int x = 0, y = 0;
	int run = 0;
	int ch;
	while(1)
	{
		if(run) start(stdscr);
		else ch = getch();
		int h, w;
		getmaxyx(stdscr, h, w);

		if( ch == ' ' )
		{
			char c = inch() == BLOCK ? ' ' : BLOCK;
			mvaddch(y, x, c);
			x++;
		}
		else if(ch == KEY_LEFT  || ch == 'h' && x-1 >= 0) x--;
		else if(ch == KEY_RIGHT || ch == 'l' && x+1 <= w) x++;
		else if(ch == KEY_DOWN  || ch == 'j' && y+1 <= h) y++;
		else if(ch == KEY_UP    || ch == 'k' && y-1 >= 0) y--;
		else if(ch == '\x0A') run = !run; // ENTER
		else if(ch == '\x1B' || ch == 'q') break; // ESC
		move(y, x);
		refresh();
	}

	endwin();
}
