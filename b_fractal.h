#ifndef B_FRACTAL_H
# define B_FRACTAL_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef	struct	s_wnd
{
	int maxIterations;
	int width;
	int height;
	void *mlx;
	void *win;
	long double cx;
	long double cy;
	long double scale;
	long double limit;
	long double a1, b1, a2, b2;
	int x, y;
	long double ax, ay;
	int *colors;
}				t_wnd;

#endif