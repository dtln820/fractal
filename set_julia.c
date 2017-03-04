/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_julia.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddulgher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:56:36 by ddulgher          #+#    #+#             */
/*   Updated: 2017/03/04 13:29:27 by ddulgher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_fractal.h"

void	ft_fillj(t_wnd *ws)
{
	ws->width = 1280;
	ws->height = 720;
	ws->mlx = mlx_init();
	ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Julia Set");
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image,
			&(ws->bits), &(ws->sizel), &(ws->endi));
	ws->cx = 0;
	ws->cy = 0;
	ws->ax = -0.8;
	ws->ay = 0.156;
	ws->scale = 0.005;
	ws->decincvar = 50;
	ws->maxiterations = 200;
	ws->col_type = 0;
	ws->mmotion = 0;
	ws->type = 1;
	ws->colors = (int*)malloc(sizeof(int) * ws->maxiterations);
	ft_makecolors(ws->maxiterations, ws->colors);
}

void	ft_drawjixel(t_wnd *ws, int x, int y)
{
	int	i;

	i = 0;
	while (i < ws->maxiterations &&
			((ws->a1 * ws->a1) + (ws->b1 * ws->b1)) < (1 << 16))
	{
		i++;
		ws->a2 = ws->a1 * ws->a1 - ws->b1 * ws->b1 + ws->ax;
		ws->b2 = 2 * ws->a1 * ws->b1 + ws->ay;
		ws->a1 = ws->a2;
		ws->b1 = ws->b2;
	}
	ft_getcolor(x, y, i, ws);
}

int		ft_drawjset(void *vws)
{
	int		x;
	int		y;
	t_wnd	*ws;

	ws = (t_wnd*)vws;
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image,
			&(ws->bits), &(ws->sizel), &(ws->endi));
	x = -1 * ws->width / 2;
	while (x < ws->width / 2)
	{
		y = -1 * ws->height / 2;
		while (y < ws->height / 2)
		{
			ws->a1 = ws->cx + x * ws->scale;
			ws->b1 = ws->cy + y * ws->scale;
			ft_drawjixel(ws, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(ws->mlx, ws->win, ws->image, 0, 0);
	mlx_destroy_image(ws->mlx, ws->image);
	ft_showinfo(ws);
	return (0);
}

int		ft_mactionj(int x, int y, t_wnd *ws)
{
	static int	prevx;
	static int	prevy;
	float		var;

	if (x >= 0 && y >= 0 && x <= ws->width
			&& y <= ws->height && ws->mmotion == 1)
	{
		if (abs((prevx + prevy) - (x + y)) > 25)
		{
			prevx = x;
			prevy = y;
			var = ((float)rand() / (float)(RAND_MAX)) * 2;
			ws->ax = 0.7885 * cos(var);
			ws->ay = 0.7885 * sin(var);
			ft_drawjset(ws);
		}
	}
	return (0);
}
