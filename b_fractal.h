#ifndef B_FRACTAL_H
# define B_FRACTAL_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

typedef	struct	s_wnd
{
	int maxIterations;
	int width;
	int height;
	int col_type;
	int mmotion;
	void *mlx;
	void *win;
	void *image;
	int bits;
	int sizel;
	int endi;
	char *im_buf;
	long double cx;
	long double cy;
	long double scale;
	long double a1, b1, a2, b2;
	long double ax, ay;
	int decincvar;
	int *colors;
}				t_wnd;

#endif
