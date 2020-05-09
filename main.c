// Any live cell with fewer than two live neighbours dies
// Any live cell with two or three live neighbours lives
// Any live cell with more than three live neighbours dies
// Any dead cell with exactly three live neighbours comes to life

#include <unistd.h>
#include <string.h>

#include "game.h"

#define TAB '\x09'
#define ENTER '\x0A'
#define ESC '\x1B'

void
write_label(void)
{
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(1));
	mvprintw(h-1, 0, "RUNNING");
	attroff(COLOR_PAIR(1));
}

void
clear_label(int h, int y, int x)
{
	move(h-1, 0);
	clrtoeol();
	move(y, x);
}

int
main(int argc, char** argv)
{
	config* cfg = malloc(sizeof(config));
	cfg->sleep = 250000;
	cfg->help = 0;
	cfg->interactive = 0;
	cfg->path = NULL;

	char c;
	while((c = getopt(argc, argv, "hif:s:")) != -1)
	{
		switch(c)
		{
			case 'h':
				cfg->help = 1;
				break;
			case 'i':
				cfg->interactive = 1;
				break;
			case 'f':
				cfg->path = calloc(sizeof(char), strlen(optarg));
				strcpy(cfg->path, optarg);
				break;
			case 's':
				cfg->sleep = atoi(optarg);
				break;
			case '?':
				if(optopt == 's')
				{
					fprintf(stderr, "Option -%c requires an argument", optopt);
				}

				puts("\n");
				cfg->help = 1;
				break;
		}

		if(cfg->help) break;
	}

	if(!cfg->interactive && cfg->path == NULL)
	{
		printf("You need to either specify a file path or use the interactive option");
		cfg->help=1;
	}

	if(cfg->help)
	{
		printf("ducgol [opt]\n"
			      "\t -h		Display this help message\n"
			      "\t -i		Run in interactive mode\n"
			      "\t -f path	Read template from file\n"
			      "\t -s n		Set number of microseconds between each iteration\n");

		return 0;
	}

	initscr();
	cbreak();
	nodelay(stdscr, 1);
	noecho();
	keypad(stdscr, TRUE);

	int run = 0;
	int x = 0, y = 0;
	int ch;
	while(1)
	{
		ch = getch();
		int h, w;
		getmaxyx(stdscr, h, w);

		if(ch == FIELD)
		{
			char c = inch() == BLOCK ? FIELD : BLOCK;
			mvaddch(y, x, c);
			x++;
		}
		else if((ch == KEY_LEFT  || ch == 'h') && x-1 >= 0) x--;
		else if((ch == KEY_RIGHT || ch == 'l') && x+1 <= w) x++;
		else if((ch == KEY_DOWN  || ch == 'j') && y+1 <= h) y++;
		else if((ch == KEY_UP    || ch == 'k') && y-1 >= 0) y--;

		else if(ch == TAB)
		{
			if(run) clear_label(h, y, x);
			run = !run;
		}
		else if(ch == ESC || ch == 'q') break;
		else if(ch == ENTER || run)
		{
			step(stdscr);
			usleep(cfg->sleep);
			start_color();
			if(run) write_label();
		}
		move(y, x);
		refresh();
	}

	endwin();
}
