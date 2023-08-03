#ifndef MODES_H
#define MODES_H

#include "struct.h"

#define MV 1
#define MR 2
#define MP 4
#define MH 8
#define MJ 16
#define MK 32
#define ML 64
#define EZ 1
#define E1 2
#define EI 4

#define fto1(x) ((x)?1:0)
#define F(x, y) fto1(x&y)
#define V(x) fto1(x&MV)
#define R(x) fto1(x&MR)
#define P(x) fto1(x&MP)
#define H(x) fto1(x&MH)
#define J(x) fto1(x&MJ)
#define K(x) fto1(x&MK)
#define L(x) fto1(x&ML)
#define Z(x) fto1(x&EZ)
#define O(x) fto1(x&E1)
#define I(x) fto1(x&EI)

#define setf(x, y) x|y
#define unsetf(x, y) x&~y
#define switchf(x,y) (F(x,y)?unsetf(x,y):setf(x,y))

int		change_color(char color, WINDOW *win, WINDOW *wui);
struct vect	get_mov_v(unsigned char *mov_mod);
void		move_curs(struct vect *c, struct ptng *p,
			struct vect v);
void		edit_pntg(WINDOW *win, struct vect *c, struct ptng *p,
			unsigned char *edt_mod, char color);

#endif

//by d0pelrh
