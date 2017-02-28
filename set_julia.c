#include "b_fractal.h"

void ft_makecolors(int max, int *colors)
{
	int i;
	int basecolor;

	basecolor = 1651275; // !0xe74c3c 0xd35400 0xf1c40f 0x9e9e9e !0x795548
	i = 0;
	while (i < max)
	{
		colors[i] = basecolor + i * 10;
		i++;
	}
}

void ft_fillstruct(t_wnd *ws)
{
	ws->width = 1280;
	ws->height = 720;
	ws->mlx = mlx_init();
	ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Mandelbrot Set");
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image, &(ws->bits), &(ws->sizel), &(ws->endi));
	ws->cx = 0;
	ws->cy = 0;
	ws->scale = 0.005;
	ws->decincvar = 50;
	ws->maxIterations = 200;
	ws->colors = (int*)malloc(sizeof(int) * ws->maxIterations);
	ft_makecolors(ws->maxIterations, ws->colors);
}

void ft_putpixel(t_wnd *ws, int x, int y, int color)
{
	int i;

	i = x * ws->bits / 8 + y * ws->sizel;
	ws->im_buf[i] = color & 0xFF;
	ws->im_buf[i + 1] = (color & 0xFF00) >> 8;
	ws->im_buf[i + 2] = (color & 0xFF0000) >> 16;
}

int ft_drawmset(void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	mlx_destroy_image(ws->mlx, ws->image);
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image, &(ws->bits), &(ws->sizel), &(ws->endi));
	for (int x = -1 * ws->width / 2; x < ws->width / 2; x++)
	{
		for(int y = -1 * ws->height / 2; y < ws->height / 2; y++)
		{
			ws->ax = -0.8;
			ws->ay = 0.156;
			ws->a1 = ws->cx + x * ws->scale;
			ws->b1 = ws->cy + y * ws->scale;
			int i = 0;
			while (i < ws->maxIterations && ((ws->a1 * ws->a1) + (ws->b1 * ws->b1)) <  (1 << 16))
			{
				i++;
				ws->a2 = ws->a1 * ws->a1 - ws->b1 * ws->b1 + ws->ax;
				ws->b2 = 2 * ws->a1 * ws->b1 + ws->ay;
				ws->a1 = ws->a2;
				ws->b1 = ws->b2;
			}
			if (i >= ws->maxIterations)
				ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, 0x000000);
			else
				ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, ws->colors[i]);
		}
	}
	mlx_put_image_to_window(ws->mlx, ws->win, ws->image, 0, 0);
	return 0;
}

int mouse_hook(int button, int x, int y, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	if (button == 4)
	{
		printf("Zoom in!\n");
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale / 2;
		return (ft_drawmset(ws));
	}
	else if (button == 5)
	{
		printf("Zoom out!\n");
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale * 2;
		return (ft_drawmset(ws));
	}
	else
		printf("Pressed some click\n");
	return 0;
}

int key_hook(int k, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	printf("pressed k = %d\n", k);
	if (k == 12)
	{
		ws->maxIterations += ws->decincvar;
		if (ws->maxIterations >= 100)
			ws->decincvar = 50;
		free(ws->colors);
		ws->colors = (int*)malloc(sizeof(int) * ws->maxIterations);
		ft_makecolors(ws->maxIterations, ws->colors);
		return (ft_drawmset(ws));
	}
	else if (k == 14)
	{
		ws->maxIterations -= ws->decincvar;
		if (ws->maxIterations <= 100)
			ws->decincvar = 10;
		free(ws->colors);
		ws->colors = (int*)malloc(sizeof(int) * ws->maxIterations);
		ft_makecolors(ws->maxIterations, ws->colors);
		return (ft_drawmset(ws));
	}
	else if (k == 53)
		exit(1);
	else
		return 0;
}

int main()
{
	t_wnd *ws;

	ws = malloc(sizeof(t_wnd));
	ft_fillstruct(ws);
	mlx_key_hook(ws->win, &key_hook, ws);
	mlx_mouse_hook(ws->win, &mouse_hook, ws);
	mlx_expose_hook(ws->win, &ft_drawmset, ws);
	mlx_loop(ws->mlx);
	return 0;
}
