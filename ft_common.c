#include "b_fractal.h"

void ft_makecolors(int max, int *colors)
{
	int i;
	int basecolor;

	basecolor = 0x2E8B57;
	i = 0;
	while (i < max)
	{
		colors[i] = basecolor + i * 10;
		i++;
	}
}

void ft_putpixel(t_wnd *ws, int x, int y, int color)
{
	int i;

	i = x * ws->bits / 8 + y * ws->sizel;
	ws->im_buf[i] = color & 0xFF;
	ws->im_buf[i + 1] = (color & 0xFF00) >> 8;
	ws->im_buf[i + 2] = (color & 0xFF0000) >> 16;
}

void ft_showinfo(t_wnd *ws)
{
	mlx_string_put(ws->mlx, ws->win, 5, 10, 0xFFFFFF, "INFO");
	mlx_string_put(ws->mlx, ws->win, 15, 30, 0xFFFFFF, "Coloring: ");
	if (ws->col_type == 1)
		mlx_string_put(ws->mlx, ws->win, 150, 30, 0xFFFFFF, "ON");
	else
		mlx_string_put(ws->mlx, ws->win, 150, 30, 0xFFFFFF, "OFF");
	mlx_string_put(ws->mlx, ws->win, 15, 50, 0xFFFFFF, "Mouse impact: ");
	if (ws->mmotion == 1)
		mlx_string_put(ws->mlx, ws->win, 150, 50, 0xFFFFFF, "ON");
	else
		mlx_string_put(ws->mlx, ws->win, 150, 50, 0xFFFFFF, "OFF");
}

void ft_getcolor(int x, int y, int i, t_wnd *ws)
{
	if (i >= ws->maxIterations)
		ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, 0x000000);
	else if (ws->col_type == 0)
		ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, i % 256);
	else
		ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, ws->colors[i]);
}

int mouse_hook(int button, int x, int y, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	if (button == 4)
	{
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale / 2;
		return (ft_drawnset(ws));
	}
	else if (button == 5)
	{
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale * 2;
		return (ft_drawnset(ws));
	}
	return (0);
}

int key_hook2(int k, t_wnd *ws)
{
	if (k == 53)
	  exit(1);
	else if (k == 17)
	{
	  if (ws->col_type == 0)
	    ws->col_type = 1;
	  else
	    ws->col_type = 0;
	  return (ft_drawnset(ws));
	}
	else if (k == 46)
	{
	  if (ws->mmotion == 0)
	    ws->mmotion = 1;
	  else
	    ws->mmotion = 0;
	  return (ft_drawnset(ws));
	}
	else
	  return 0;
}

int key_hook(int k, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	if (k == 12)
	{
		ws->maxIterations += ws->decincvar;
		if (ws->maxIterations >= 100)
			ws->decincvar = 50;
		free(ws->colors);
		ws->colors = (int*)malloc(sizeof(int) * ws->maxIterations);
		ft_makecolors(ws->maxIterations, ws->colors);
		return (ft_drawnset(ws));
	}
	else if (k == 14)
	{
		ws->maxIterations -= ws->decincvar;
		if (ws->maxIterations <= 100)
			ws->decincvar = 10;
		free(ws->colors);
		ws->colors = (int*)malloc(sizeof(int) * ws->maxIterations);
		ft_makecolors(ws->maxIterations, ws->colors);
		return (ft_drawnset(ws));
	}
	else
		return (key_hook2(k, ws));
}
