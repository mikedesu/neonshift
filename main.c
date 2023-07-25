#include <ncurses.h>
#include <stdlib.h> //malloc
#include <time.h> //CLOCKS_PER_SEC clock
#include <unistd.h> //usleep
//
#include "struct.h" //structs: curs ptng, constants

int	main(int ac, char **av){
initscr(); // = NCURSES INIT ===
cbreak(); noecho();
nodelay(stdscr, TRUE);
//curs_set(0);
start_color(); // ==============

WINDOW		*win;
struct curs	curs;
struct ptng	ptng;
clock_t		clk_start, clk;
FILE		*file;
//
int		refresh_rate;
char		c, f, color;

curs.i = 0; curs.c = '.';
curs.fps = BASE_FPS; refresh_rate = CLOCKS_PER_SEC/curs.fps;
ptng.w = BASE_W; ptng.h = BASE_H; ptng.size = ptng.w*ptng.h;
ptng.buf = (short *)malloc(ptng.size*sizeof(short));
for (int i=0; i<ptng.size; i++) ptng.buf[i] = 0;
f = 1; color = 2;

init_pair(1, 10, 0); //green foreground
init_pair(2, 0, 10); //green background
refresh(); win = newwin(ptng.h+2, ptng.w+2, 3, 7);
box(win, 0, 0); wrefresh(win); delwin(win);
win = newwin(ptng.h, ptng.w, 4, 8);

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
case 'z': if (f == 'z') f = 1; else f = 'z'; break;
default: break;}}

else {
if (f == 'z'){
	waddch(win, ' ');
	if (ptng.buf[curs.i]) ptng.buf[curs.i] = 0;
	else ptng.buf[curs.i] = 1;}
else wmove(win, (curs.i+1)/ptng.w, (curs.i+1)%ptng.w);
curs.i++;}

if (curs.i == ptng.size){
	if (color == 2) color = 1; else color = 2;
	wattron(win, COLOR_PAIR(color)); f = 1;
	curs.i = 0; wmove(win, 0, 0);}
wrefresh(win);

clk = clock() - clk_start;
usleep((refresh_rate-clk)*(1000000/CLOCKS_PER_SEC));
clk_start = clock();			}

free(ptng.buf);
delwin(win); endwin();
return 0;}
