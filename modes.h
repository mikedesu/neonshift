#ifndef MODES_H
#define MODES_H

#include <ncurses.h>
#include "struct.h"

int	mode_n_update(char *flag, WINDOW *win, WINDOW *wui,
		struct ptng *p, struct curs *c, char *color);
int	mode_r_update(char *flag, WINDOW *win, WINDOW *wui,
		struct ptng *p, struct curs *c, char *color);

int	change_color(char *color, WINDOW *win, WINDOW *wui);

#endif
