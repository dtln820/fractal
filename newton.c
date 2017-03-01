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

void ft_fillstruct(t_wnd *ws)
{
	ws->width = 1280;
	ws->height = 720;
	ws->mlx = mlx_init();
	ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Julia Set");
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image, &(ws->bits), &(ws->sizel), &(ws->endi));
	ws->cx = 0;
	ws->cy = 0;
	ws->ax = 0.4;
	ws->ay = 0.4;
	ws->scale = 0.005;
	ws->decincvar = 50;
	ws->maxIterations = 200;
	ws->col_type = 0;
	ws->mmotion = 0;
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

void ft_showinfo(t_wnd *ws)
{
	char *colors;
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

int ft_drawmset(void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image, &(ws->bits), &(ws->sizel), &(ws->endi));
	for (int x = -1 * ws->width / 2; x < ws->width / 2; x++)
	{
		for(int y = -1 * ws->height / 2; y < ws->height / 2; y++)
		{
			ws->a1 = ws->cx + x * ws->scale;
			ws->b1 = ws->cy + y * ws->scale;
			int i = 0;
			while (i < ws->maxIterations && ((ws->a1 * ws->a1) + (ws->b1 * ws->b1)) <  (1 << 16))
			{
				i++;
				ws->a2 = ws->a1 * ws->a1 * ws->a1 - 3 * ws->a1 * ws->b1 * ws->b1 + ws->ax;
				ws->b2 = 3 * ws->a1 * ws->a1 * ws->b1 - ws->b1 * ws->b1 * ws->b1 + ws->ay;
				ws->a1 = ws->a2;
				ws->b1 = ws->b2;
			}
			if (i >= ws->maxIterations)
				ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, 0x000000);
			else if (ws->col_type == 0)
				ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, i % 256);
			else
				ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, ws->colors[i]);
		}
	}
	mlx_put_image_to_window(ws->mlx, ws->win, ws->image, 0, 0);
	mlx_destroy_image(ws->mlx, ws->image);
	ft_showinfo(ws);
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
		printf("Some click was done.");
	return (0);
}

int key_hook(int k, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	printf("k == %d\n", k);
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
	else if (k == 17) // T key_hook
	{
		if (ws->col_type == 0)
			ws->col_type = 1;
		else
			ws->col_type = 0;
		return (ft_drawmset(ws));
	}
	else if (k == 46) // M key_hook
	{
		if (ws->mmotion == 0)
			ws->mmotion = 1;
		else
			ws->mmotion = 0;
		return (ft_drawmset(ws));
	}
	else
		return 0;
}

int ft_mouse_action(int x, int y, t_wnd *ws)
{
	static int prevx = 0, prevy = 0;
	static int i = 0;
	if (x >= 0 && y >= 0 && x <= ws->width && y <= ws->height && ws->mmotion == 1)
	{
		if (abs((prevx + prevy) - (x + y)) > 25)
		{
			prevx = x;
			prevy = y;
			float var;
			var = ((float)rand() / (float)(RAND_MAX)) * 2;
			ws->ax = 0.7885 * cos(var);
			ws->ay = 0.7885 * sin(var);
			i++;
			ft_drawmset(ws);
		}
	}
	return 0;
}

int main()
{
	time_t t;
	srand((unsigned) time(&t));
	t_wnd *ws;

	ws = malloc(sizeof(t_wnd));
	ft_fillstruct(ws);
	mlx_key_hook(ws->win, &key_hook, ws);
	mlx_mouse_hook(ws->win, &mouse_hook, ws);
	mlx_expose_hook(ws->win, &ft_drawmset, ws);
	mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mouse_action, ws);
	mlx_loop(ws->mlx);
	return 0;
}
