#ifndef STRUCT_H
#define STRUCT_H

#define BASE_W 70
#define BASE_H 20
#define BASE_FPS 50

struct	curs{
	int	i;
	char	c;
	int	fps;
};

struct	ptng{
	short	w;
	short	h;
	int	size;
	short	*buf;
};

#endif
