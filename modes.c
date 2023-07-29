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
		switchf(*mov_mod, MH);
		v.y = 0; v.x = -1;}
	else if (J(*mov_mod)){
		switchf(*mov_mod, MJ);
		v.y = 1; v.x = 0;}
	else if (K(*mov_mod)){
		switchf(*mov_mod, MK);
		v.y = -1; v.x = 0;}
	else if (L(*mov_mod)){
		switchf(*mov_mod, ML);
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

