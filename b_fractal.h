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
	double cx;
	double cy;
	double scale;
	int limit;
	double a1, b1, a2, b2;
	int x, y;
	double ax, ay;
}				t_wnd;

#endif