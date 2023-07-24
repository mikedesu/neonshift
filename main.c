#include <ncurses.h>
#include <stdlib.h> //malloc
#include <time.h> //CLOCKS_PER_SEC clock
#include <unistd.h> //usleep

#include "struct.h"

int	main(int ac, char **av){
initscr(); // = NCURSES INIT ===
cbreak();
noecho();
//nodelay(stdscr, TRUE);
//curs_set(0); // ================
WINDOW	*win;
struct curs	curs;
struct ptng	ptng;
clock_t	clk_start, clk;
int	fps, refresh_rate;

curs.i = 0; curs.c = '.';
ptng.w = 70; ptng.h = 20;
ptng.buf = (int *)malloc(70*20*sizeof(int));
for (int i=0; i<70*20; i++)
	ptng.buf[i] = 0;
fps = 5;
refresh_rate = CLOCKS_PER_SEC/fps;

refresh();
win = newwin(22, 72, 3, 7);
box(win, 0, 0);
wrefresh(win);
getch();
delwin(win);

win = newwin(20, 70, 4, 8);

clk_start = clock(); while (1){

wprintw(win, "x"); curs.i++;

if (curs.i == ptng.w*ptng.h){
	curs.i = 0;
	wmove(win, 0, 0);}

wrefresh(win);

clk = clock() - clk_start;
if (clk < refresh_rate)
	usleep((refresh_rate-clk)*(1000000/CLOCKS_PER_SEC));
clk_start = clock();}



delwin(win);
endwin();
return 0;}
