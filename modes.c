#include <ncurses.h>

#include "modes.h"
#include "struct.h"

int	mode_n_update(char *flag, WINDOW *win, WINDOW *wui,
		struct ptng *p, struct curs *c, char *color){
if (*flag == 'z'){
	waddch(win, ' ');
	if (p->buf[c->i]) p->buf[c->i] = 0;
	else p->buf[c->i] = 1;}
else wmove(win, (c->i+1)/p->w, (c->i+1)%p->w);
c->i++;
if (c->i == p->size){
	if (*color == 2) *color = 1; else *color = 2;
	change_color(color, win, wui); *flag = 1;
	c->i = 0; wmove(win, 0, 0);}
return 0;}


int	mode_r_update(char *flag, WINDOW *win, WINDOW *wui,
		struct ptng *p, struct curs *c, char *color){
if (*flag == 'z'){
	wmove(win, (c->i+1)/p->w, (c->i+1)%p->w-2);
	waddch(win, ' ');
	if (p->buf[c->i]) p->buf[c->i] = 0;
	else p->buf[c->i] = 1;}
else wmove(win, (c->i+1)/p->w, (c->i+1)%p->w-1);
c->i--;
if (c->i == 0){
	if (*color == 2) *color = 1; else *color = 2;
	change_color(color, win, wui); *flag = 1;
	c->i = p->size-1; wmove(win, p->h-1, p->w-1);}
return 0;}

int	change_color(char *color, WINDOW *win, WINDOW *wui){
	wattron(win, COLOR_PAIR(*color));
	wattron(wui, COLOR_PAIR(*color));
	mvwprintw(wui, 2, 0, "c c c\n");
	wprintw(wui, "c c c"); wrefresh(wui);
	wattroff(wui, COLOR_PAIR(*color));
return 0;}
