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

void ft_makecolors(int max, int *colors);

void ft_putpixel(t_wnd *ws, int x, int y, int color);

void ft_showinfo(t_wnd *ws);

void ft_getcolor(int x, int y, int i, t_wnd *ws);

int mouse_hook(int button, int x, int y, void *vws);

int key_hook2(int k, t_wnd *ws);

int key_hook(int k, void *vws);

int ft_mactionn(int x, int y, t_wnd *ws);

int ft_drawnset(void *vws);

void ft_drawnixel(t_wnd *ws, int x, int y);

void ft_filln(t_wnd *ws);

void ft_fillj(t_wnd *ws);

void ft_drawjixel(t_wnd *ws, int x, int y);

int ft_drawjset(void *vws);

int ft_mactionj(int x, int y, t_wnd *ws);

void ft_fillm(t_wnd *ws);

void ft_drawmixel(t_wnd *ws, int x, int y);

int ft_drawmset(void *vws);

int ft_mactionb(int x, int y, t_wnd *ws);

void    ft_putstr(char const *s);

int     ft_strcmp(const char *str1, const char *str2);

#endif
