#ifndef B_FRACTAL_H
# define B_FRACTAL_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef	struct	s_wnd
{
	void *mlx;
	void *win;
	int cx;
	int cy;
	int width;
	int height;
	int limit;
	int max;
	int *colors;
	double scale;
}				t_wnd;

#endif