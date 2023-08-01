#include <ncurses.h>
#include <stdlib.h> //malloc
#include <time.h> //CLOCKS_PER_SEC clock
#include <unistd.h> //usleep
#include "struct.h" //structs: curs ptng, constants
#include "modes.h" //constants, macros, functioning

int	main(int ac, char **av){
initscr(); cbreak(); noecho();
nodelay(stdscr, TRUE);
start_color(); //curs_set(0);

WINDOW		*win, *wui;
clock_t		clk_start, clk;
struct vect	curs, mov_v, sweep_v;
struct ptng	ptng;
FILE		*file;
unsigned char	mov_mod, edt_mod;
int		refresh_rate, fps;
char		color;
char		c, q;
//char	z = 'z';

fps = BASE_FPS; refresh_rate = CLOCKS_PER_SEC/fps;
ptng.w = BASE_W; ptng.h = BASE_H; ptng.size = ptng.w*ptng.h;
ptng.buf = (char *)malloc(ptng.size);
curs.y = ptng.h-1; curs.x = ptng.w-1;
mov_mod = 2; edt_mod = 0; color = 2;
q = 1;

refresh();
init_pair(1, 10, 0); //black
init_pair(2, 0, 10); //green
win = newwin(ptng.h+2, ptng.w+2, 3, 7);
wattron(win, COLOR_PAIR(1));
box(win, 0, 0); wrefresh(win); delwin(win);
win = newwin(ptng.h, ptng.w, 4, 8);
wui = newwin(10, 10, 4, 9+ptng.w+5);
wattron(wui, COLOR_PAIR(1));
mvwprintw(wui, 1, 0, (O(edt_mod)?"\nspot \n":"\nstroke\n"));
wattron(wui, COLOR_PAIR(color));
mvwprintw(wui, 4, 0, "c c c\nc c c\n\n");
wattron(wui, COLOR_PAIR(1));
wprintw(wui, "fps: %i\n", fps); wrefresh(wui);

if ((file=fopen("painting", "r"))) { int i=0;
	while ((c=fgetc(file)) != EOF){
		c = fgetc(file); switch(c){
		case '9': ptng.buf[i] = 0;
			wattron(win, COLOR_PAIR(1));
			waddch(win, ' '); break;
		case '1': ptng.buf[i] = 1;
			wattron(win, COLOR_PAIR(2));
			waddch(win, ' '); break;
		defautl: break;}  i++;
		fgetc(file); fgetc(file); fgetc(file);
		if (!(i%ptng.w)) fgetc(file);}
	fclose(file); wrefresh(win);}
else for (int i=0; i<ptng.size; i++) ptng.buf[i] = 0;

wattron(win, COLOR_PAIR(color));
clk_start = clock();
/* ========================== */	while (q){	/*====*/

if ((c=getch())!=ERR){ switch(c){
case 'q': q = 0; break;
case 's': file = fopen("painting", "w");
	for (int i=0; i<ptng.size; i++){ switch(ptng.buf[i]){
		case 0:	//black
			fputc(3, file);
			fprintf(file, "9,1 "); break;
		case 1: //green
			fputc(3, file);
			fprintf(file, "1,9 "); break;
		default: break;}
		if (i && !((i+1)%ptng.w)) fputc('\n', file);}
	fclose(file); break;

case 'c': if (color == 2) color = 1; else color = 2;
	change_color(color, win, wui); break;
case '-': if(fps>1) fps--; refresh_rate = CLOCKS_PER_SEC/fps;
	 mvwprintw(wui, 7, 5, "%i  ", fps);
	 wrefresh(wui); break;
case '+': fps++; refresh_rate = CLOCKS_PER_SEC/fps;
	 mvwprintw(wui, 7, 5, "%i  ", fps);
	 wrefresh(wui); break;

case 'g': mov_mod = switchf(mov_mod, MV); break;
case 'b': mov_mod = switchf(mov_mod, MR); break;
case ' ': mov_mod = switchf(mov_mod, MP); break;

case 'h': mov_mod = switchf(mov_mod, MH); break;
case 'j': mov_mod = switchf(mov_mod, MJ); break;
case 'k': mov_mod = switchf(mov_mod, MK); break;
case 'l': mov_mod = switchf(mov_mod, ML); break;

case 'z': edt_mod = switchf(edt_mod, EZ); break;
case ';': edt_mod = switchf(edt_mod, E1);
	  mvwprintw(wui, 1, 0, (O(edt_mod)?"spot  ":"stroke"));
	  wrefresh(wui); break;
case 'p': edt_mod = switchf(edt_mod, EI);
	  mvwprintw(wui, 2, 0, (I(edt_mod)?"invert":"      "));
	  wrefresh(wui); break;
default: break;}}

mov_v = get_mov_v(&mov_mod);
move_curs(&curs, &ptng, mov_v);
edit_pntg(win, &curs, &ptng, &edt_mod, color);

wrefresh(win);
clk = clock()-clk_start;
usleep((refresh_rate-clk)*(1000000/CLOCKS_PER_SEC));
clk_start = clock();	/* ================== */	}	/*====*/

free(ptng.buf);
delwin(win); delwin(wui); endwin();
return 0;}
