#ifndef STRUCT_H
#define STRUCT_H

#define BASE_W 70
#define BASE_H 20
#define BASE_FPS 20

struct	vect{
	char	y;
	char	x;
};

struct	ptng{
	short	w;
	short	h;
	int	size;
	char	*buf;
};

#endif
