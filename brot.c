#include "b_fractal.h"

void ft_fillstruct(t_wnd *ws)
{
	ws->width = 640;
	ws->height = 480;
	ws->mlx = mlx_init();
	ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Mandelbrot Set");
	ws->cx = 0;
	ws->cy = 0;
	ws->scale = 0.005;
	ws->limit = 4;
	ws->zoomnr = 0;
	ws->maxIterations = 255;
}

int ft_drawmset(void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	for (int x = -1 * ws->width / 2; x < ws->width / 2; x++)
	{
		for(int y = -1 * ws->height / 2; y < ws->height / 2; y++)
		{
			ws->ax = ws->cx + x * ws->scale;
			ws->ay = ws->cy + y * ws->scale;
			ws->a1 = ws->ax;
			ws->b1 = ws->ay;
			int i = 0;
			while (i < ws->maxIterations && ((ws->a1 * ws->a1) + (ws->b1 * ws->b1)) < ws->limit)
			{
				i++;
				ws->a2 = ws->a1 * ws->a1 - ws->b1 * ws->b1 + ws->ax;
				ws->b2 = 2 * ws->a1 * ws->b1 + ws->ay;
				ws->a1 = ws->a2;
				ws->b1 = ws->b2;
			}
			if (i >= ws->maxIterations)
				mlx_pixel_put(ws->mlx, ws->win, x + ws->width / 2, y + ws->height / 2, 0x000000);
			else
			{
				double z = sqrt(ws->a2 * ws->a2 + ws->b2 * ws->b2);
				int brightness = 256.0 * log2(1.75 + i - log2(log2(z))) / log2((double)ws->maxIterations);
				int color = brightness * brightness * 255;
				mlx_pixel_put(ws->mlx, ws->win, x + ws->width / 2, y + ws->height / 2, color);
			}
		}
	}
	return 0;
}

int mouse_hook(int button, int x, int y, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	if (button == 4)
	{
		ws->zoomnr = ws->zoomnr + 1;
		printf("Zoom in!\n");
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale / 2;
		return (ft_drawmset(ws));
	}
	else if (button == 5)
	{
		printf("Zoom out!\n");
		ws->cx = ws->cx - ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy - ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale * 2;
		return (ft_drawmset(ws));
	}
	else
		printf("Pressed some shit\n");
	return 0;
}

int key_hook(int k, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	printf("pressed k = %d\n", k);
	if (k == 113)
	{
		ws->maxIterations += 250;
		return (ft_drawmset(ws));
	}
	else if (k == 101)
	{
		ws->maxIterations -= 250;
		return (ft_drawmset(ws));
	}
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