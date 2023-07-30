#include <ncurses.h>
#include "modes.h"

int	change_color(char *color, WINDOW *win, WINDOW *wui){
	wattron(win, COLOR_PAIR(*color));
	wattron(wui, COLOR_PAIR(*color));
	mvwprintw(wui, 2, 0, "c c c\n");
	wprintw(wui, "c c c"); wrefresh(wui);
	wattroff(wui, COLOR_PAIR(*color));
return 0;}

struct vect	get_mov_v(unsigned char *mov_mod){
struct vect	v;
	if (H(*mov_mod)){
		*mov_mod = switchf(*mov_mod, MH);
		v.y = 0; v.x = -1;}
	else if (J(*mov_mod)){
		*mov_mod = switchf(*mov_mod, MJ);
		v.y = 1; v.x = 0;}
	else if (K(*mov_mod)){
		*mov_mod = switchf(*mov_mod, MK);
		v.y = -1; v.x = 0;}
	else if (L(*mov_mod)){
		*mov_mod = switchf(*mov_mod, ML);
		v.y = 0; v.x = 1;}
	else if (P(*mov_mod)){
		v.y = 0; v.x = 0;}
	else if (!V(*mov_mod) && !R(*mov_mod)){
		v.y = 0; v.x = 1;}
	else if (!V(*mov_mod) && R(*mov_mod)){
		v.y = 0; v.x = -1;}
	else if (V(*mov_mod) && !R(*mov_mod)){
		v.y = 1; v.x = 0;}
	else if (V(*mov_mod) && R(*mov_mod)){
		v.y = -1; v.x = 0;}
return v;}

void	move_curs(WINDOW *win, struct curs *c,
		struct ptng *p, struct vect v,
		unsigned char mov_mod){
if (!c->y&&!c->x&&(v.y==-1||v.x==-1)){ c->y=p->h-1; c->x=p->w-1;}
else if (c->y==p->h-1&&c->x==p->w-1&&(v.y==1||v.x==1)){ c->y=0; c->x=0;}
else if (!c->y&&v.y==-1){ c->y=p->h-1; c->x--;}
else if (c->y==p->h-1&&v.y==1){ c->y=0; c->x++;}
else if (!c->x&&v.x==-1){ c->y--; c->x=p->w-1;}
else if (c->x==p->w-1&&v.x==1){ c->y++; c->x=0;}
else if (v.y==-1) c->y--;
else if (v.y==1) c->y++;
else if (v.x==-1) c->x--;
else if (v.x==1) c->x++;
wmove(win, c->y, c->x);
return;}

void	edit_pntg(WINDOW *win, struct curs *c,
		struct ptng *p, unsigned char *edt_mod,
		char color){
if (Z(*edt_mod)){
if (O(*edt_mod)) *edt_mod = switchf(*edt_mod, EZ);
if (!I(*edt_mod)){
	if (color == 1) p->buf[c->y*p->w+c->x] = 0;
	else if (color == 2) p->buf[c->y*p->w+c->x] = 1;
	waddch(win, ' ');}
else{
	if (p->buf[c->y*p->w+c->x] == 0){
		p->buf[c->y*p->w+c->x] = 1;
		wattron(win, COLOR_PAIR(2));}
	else if (p->buf[c->y*p->w+c->x] == 1){
		p->buf[c->y*p->w+c->x] = 0;
		wattron(win, COLOR_PAIR(1));}
	waddch(win, ' ');
	wattron(win, COLOR_PAIR(color));}}
return;}
