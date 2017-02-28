#include "j_fractal.h"

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
	double newRe, newIm, oldRe, oldIm;
	for (int y = 0; y < ws->height; y++)
	{
		for (int x = 0; x < ws->width; x++)
		{
			newRe = 1.5 * (x - ws->width / 2) / (0.5 * ws->width * ws->zoom) + ws->moveX;
			newIm = (y - ws->height / 2) / (0.5 * ws->height * ws->zoom) + ws->moveY;
			int i;
			for (i = 0; i <= ws->max; i++)
			{
				oldRe = newRe;
				oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + ws->cx;
				newIm = 2 * oldRe * oldIm + ws->cy;
				if ((newRe * newRe + newIm * newIm) > 4) break;
			}
			if (i > ws->max)
				mlx_pixel_put(ws->mlx, ws->win, x, y, 0x000000);
			else
				mlx_pixel_put(ws->mlx, ws->win, x, y, ws->colors[i]); // (i % 256 * 255 * 255)
		}
	}
	printf("moveX = %f\n", ws->moveX);
	printf("moveY = %f\n", ws->moveY);
	printf("ws->width / 2 = %d\n", ws->width + 1 / 2);
	printf("ws->width * 0.5 = %f\n", ws->width + 1 * 0.5);
	mlx_pixel_put(ws->mlx, ws->win, ws->width / 2, ws->height / 2, 0xFFFFFF);
	printf("prevx = %d prevy = %d\n", ws->prevx, ws->prevy);
	return 0;
}

int mouse_hook(int button, int x, int y, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	printf("button = %d\n", button);
	printf("x = %d y = %d\n", x, y);
	if (button == 1)
	{
		ws->zoom *= 2;
		if (x > ws->width / 2 && x != ws->prevx)
			ws->moveX += x * 0.0001;
		else if (x < ws->width / 2 && x != ws->prevx)
			ws->moveX -= x * 0.0003;
		if (y > ws->height / 2 && y != ws->prevy)
			ws->moveY += y * 0.00025;
		else if (y < ws->height / 2 && y != ws->prevy)
			ws->moveY -= y * 0.0003;
		ws->prevx = x;
		ws->prevy = y;
	}
	else if (button == 2)
	{
		ws->zoom /= 2;
		if (x > ws->width / 2 && x != ws->prevx)
			ws->moveX += x * 0.0003;
		else if (x < ws->width / 2 && x != ws->prevx)
			ws->moveX -= x * 0.0003;
		if (y > ws->height / 2 && y != ws->prevy)
			ws->moveY += y * 0.0003;
		else if (y < ws->height / 2 && y != ws->prevy)
			ws->moveY -= y * 0.0003;
		ws->prevx = x;
		ws->prevy = y;
	}
	else
		return 0;
	return (ft_drawmset(ws));
}

void ft_fillstruct(t_wnd *ws)
{
	ws->width = 800;
	ws->height = 600;
	ws->mlx = mlx_init();
	ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Fractal");
	ws->max = 128;
	ws->moveX = -0.5;
	ws->moveY = 0;
	ws->colors = (int*)malloc(sizeof(int) * ws->max);
	ws->zoom = 1;
	ws->prevx = 0;
	ws->prevy = 0;
	ws->cx = -0.7;
	ws->cy = 0.27015;
	// ws->cx = -0.835;
	// ws->cy = -0.2321;
	ft_makecolors(ws->max + 1, ws->colors);
}

int main()
{
	t_wnd *ws;

	ws = malloc(sizeof(t_wnd));
	ft_fillstruct(ws);
	mlx_mouse_hook(ws->win, &mouse_hook, ws);
	mlx_expose_hook(ws->win, &ft_drawmset, ws);
	mlx_loop(ws->mlx);
	return 0;
}
