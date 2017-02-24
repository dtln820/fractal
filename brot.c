#include "b_fractal.h"

void ft_makecolors(int max, int *colors)
{
	int i;
	int basecolor;

	basecolor = 1651275;
	i = 0;
	while (i < max)
	{
		colors[i] = basecolor + i * 10;
		i++;
	}
}

int ft_drawmset(void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	mlx_clear_window(ws->mlx, ws->win);
	int lp;
	double ax, ay, a1, b1, a2, b2;
	for (int x = -400; x < 399; x++)
	{
		for (int y = -300; y < 299; y++)
		{
			ax = ws->cx + x * ws->scale;
			ay = ws->cy + y * ws->scale;
			a1 = ax;
			b1 = ay;
			lp = 0;

			while (lp <= 1000 && ((a1 * a1) + (b1 * b1)) < ws->limit)
			{
				a2 = a1 * a1 - b1 * b1 + ax;
				b2 = 2 * a1 * b1 + ay;
				a1 = a2;
				b1 = b2;
				lp++;
			}
			if (lp > 1000)
				mlx_pixel_put(ws->mlx, ws->win, x + 400, y + 300, 0x000000);
			else
				mlx_pixel_put(ws->mlx, ws->win, x + 400, y + 300, ws->colors[lp]);
		}
	}
}

void ft_fillstruct(t_wnd *ws)
{
	ws->mlx = mlx_init();
	ws->width = 800;
	ws->height = 600;
	ws->win = mlx_new_window(ws->mlx, 800, 600, "Fractal");
	ws->limit = 20;
	ws->max = 1000;
	ws->scale = 0.005;
	ws->cx = 0;
	ws->cy = 0;
	ws->colors = (int*)malloc(sizeof(int) * ws->max);
	ft_makecolors(ws->max, ws->colors);
}

int mouse_hook(int button, int x, int y, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	printf("button = %d\n", button);
	printf("x = %d y = %d\n", x, y);
	if (button == 1)
	{
		ws->cx = ws->cx + ws->scale * (x - 400);
		ws->cy = ws->cy + ws->scale * (y - 300);
		ws->scale = ws->scale / 2;
	}
	else if (button == 2)
	{
		ws->cx = ws->cx - ws->scale * (x - 400);
		ws->cy = ws->cy - ws->scale * (y - 300);
		ws->scale = ws->scale * 2;
	}
	else
		return 0;
	return (ft_drawmset(ws));
}

int main()
{
	t_wnd *ws;

	ws = malloc(sizeof(t_wnd));
	ft_fillstruct(ws);
	ft_drawmset(ws);
	mlx_mouse_hook(ws->win, &mouse_hook, ws);
	mlx_expose_hook(ws->win, &ft_drawmset, ws);
	mlx_loop(ws->mlx);
	return 0;
}
