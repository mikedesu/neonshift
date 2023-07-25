#include <ncurses.h>
#include <stdlib.h> //malloc
#include <time.h> //CLOCKS_PER_SEC clock
#include <unistd.h> //usleep
//
#include "struct.h" //structs: curs ptng, constants
#include "modes.h"

int	main(int ac, char **av){
initscr(); // = NCURSES INIT ===
cbreak(); noecho();
nodelay(stdscr, TRUE);
//curs_set(0);
start_color(); // ==============

WINDOW		*win, *wui;
struct curs	curs;
struct ptng	ptng;
clock_t		clk_start, clk;
FILE		*file;
//
int		refresh_rate;
char		c, f, color, mode;
//
char	z = 'z';

curs.i = 0; curs.c = '.';
curs.fps = BASE_FPS; refresh_rate = CLOCKS_PER_SEC/curs.fps;
ptng.w = BASE_W; ptng.h = BASE_H; ptng.size = ptng.w*ptng.h;
ptng.buf = (short *)malloc(ptng.size*sizeof(short));
for (int i=0; i<ptng.size; i++) ptng.buf[i] = 0;
f = 1; color = 2; mode = 'n';

init_pair(1, 10, 0); //green foreground
init_pair(2, 0, 10); //green background
refresh(); win = newwin(ptng.h+2, ptng.w+2, 3, 7);
box(win, 0, 0); wrefresh(win); delwin(win);
win = newwin(ptng.h, ptng.w, 4, 8);
wui = newwin(20, 15, 4, 9+ptng.w+5);
wprintw(wui, "MODES\n");
wattron(wui, COLOR_PAIR(color));
wprintw(wui, "\nc c c\n");
wprintw(wui, "c c c\n\n");
wattroff(wui, COLOR_PAIR(color));
wprintw(wui, "normal\n");
wprintw(wui, "band\n");
wrefresh(wui);

wattron(win, COLOR_PAIR(color));
clk_start = clock();		 while (f){

if ((c=getch()) != ERR){ switch(c){
case 'q': f = 0; break;
case 's': file = fopen("painting", "w");
	for (int i=0; i<ptng.size; i++){ switch(ptng.buf[i]){
		case 0:	//black
			fputc(3, file);
			fprintf(file, "9,1 ");
			break;
		case 1: //green
			fputc(3, file);
			fprintf(file, "1,9 ");
			break;
		default: break;}
		if (i && !((i+1)%ptng.w)) fputc('\n', file);}
	fclose(file); break;
case 'z': if (f == 'z') f = 1;
	else if (f == 'm') {
if (mode == 'n')	
	mode_n_update(&z, win, wui, &ptng, &curs, &color);
else if (mode == 'r')
	mode_r_update(&z, win, wui, &ptng, &curs, &color);
	}
		 else f = 'z'; break;

case 'c': if (color == 2) color = 1; else color = 2;
	change_color(&color, win, wui); f = 1; break;
case 'n': if (mode == 'n'){ mode = 'r';
		mvwprintw(wui, 5, 0, "reversed");}
	else{ mode = 'n'; mvwprintw(wui, 5, 0, "normal  ");}
	wrefresh(wui); break;
case 'm': if (f == 'm'){ f = 1;
		mvwprintw(wui, 6, 0, "band");}
	else{ f = 'm'; mvwprintw(wui, 6, 0, "spot");}
	wrefresh(wui); break;
default: break;}}

else{
if (mode == 'n')	
	mode_n_update(&f, win, wui, &ptng, &curs, &color);
else if (mode == 'r')
	mode_r_update(&f, win, wui, &ptng, &curs, &color);
}
wrefresh(win);

clk = clock() - clk_start;
usleep((refresh_rate-clk)*(1000000/CLOCKS_PER_SEC));
clk_start = clock();			}

free(ptng.buf);
delwin(win); delwin(wui);
endwin();
return 0;}
