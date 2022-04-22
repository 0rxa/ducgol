#include <unistd.h>
#include <string.h>

#include "game.h"

#define TAB '\x09'
#define ENTER '\x0A'
#define ESC '\x1B'

void
write_label(int h)
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
	int RETVAL = 0;
	config* cfg = malloc(sizeof(config));
	cfg->sleep = 250000;
	cfg->help = 0;
	cfg->path = NULL;

	char c;
	while((c = getopt(argc, argv, "hf:s:")) != -1)
	{
		switch(c)
		{
			case 'h':
				cfg->help = 1;
				break;
			case 'f':
				if(!access(cfg->path, R_OK))
				{
					fprintf(stderr, "File not found or permission denied\n");
					cfg->help = 1;
					RETVAL = 1;
				}
				else
				{
					cfg->path = optarg;
				}
				break;
			case 's':
				cfg->sleep = atoi(optarg);
				if(cfg->sleep <= 0)
				{
					fprintf(stderr, "Wait time can't be less than 1\n");
					RETVAL = 1;
				}
				else cfg->sleep = atoi(optarg);
				break;
			case '?':
				if(optopt == 's') fprintf(stderr, "Option -%c requires an argument\n", optopt);
				cfg->help = 1;
				RETVAL = 1;
				break;
		}

		if(cfg->help)
		{
			printf("ducgol [opt]\n"
				      "\t -h		Display this help message\n"
				      "\t -f path	Read template from file\n"
				      "\t -s n		Set number of microseconds to wait before each iteration\n");
			return RETVAL;
		}
	}

	initscr();
	cbreak();
	nodelay(stdscr, 1);
	noecho();
	keypad(stdscr, TRUE);

	if(cfg->path != NULL)
	{
		FILE* template = fopen(cfg->path, "r");
		import_template(template, stdscr);
	}

	int run = 0;
	int x = 0, y = 0;
	int ch;
	while(1)
	{
		refresh();
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
			if(run) write_label(h);
		}
		move(y, x);
	}

	endwin();
}
