#include <ncurses.h>
#include <stdlib.h> //malloc
#include <time.h> //CLOCKS_PER_SEC clock
#include <unistd.h> //usleep

#include "struct.h" //structs: curs ptng, constants

int	main(int ac, char **av){
initscr(); // = NCURSES INIT ===
cbreak();
noecho();
//nodelay(stdscr, TRUE);
//curs_set(0); // ==============

WINDOW		*win;
struct curs	curs;
struct ptng	ptng;
clock_t		clk_start, clk;
int		refresh_rate;

curs.i = 1; curs.c = '.';
curs.fps = BASE_FPS; refresh_rate = CLOCKS_PER_SEC/curs.fps;
ptng.w = BASE_W; ptng.h = BASE_H; ptng.size = ptng.w*ptng.h;
ptng.buf = (short *)malloc(ptng.size*sizeof(int));
for (int i=0; i<70*20; i++) ptng.buf[i] = 0;

refresh(); win = newwin(ptng.h+2, ptng.w+2, 3, 7);
box(win, 0, 0); wrefresh(win); delwin(win);

win = newwin(ptng.h, ptng.w, 4, 8);

clk_start = clock(); while (1)	{

wprintw(win, "x"); curs.i++;

if (curs.i == ptng.size){
	curs.i = 0; wmove(win, 0, 0);}

wrefresh(win);

clk = clock() - clk_start;
usleep((refresh_rate-clk)*(1000000/CLOCKS_PER_SEC));
clk_start = clock();		}

delwin(win);
endwin();
return 0;}
