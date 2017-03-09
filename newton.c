/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddulgher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:52:15 by ddulgher          #+#    #+#             */
/*   Updated: 2017/03/04 13:22:37 by ddulgher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_fractal.h"

void	ft_filln(t_wnd *ws)
{
	ws->width = 1280;
	ws->height = 720;
	ws->mlx = mlx_init();
	ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Random Set");
	ws->image = mlx_new_image(ws->mlx, ws->width, ws->height);
	ws->im_buf = mlx_get_data_addr(ws->image,
			&(ws->bits), &(ws->sizel), &(ws->endi));
	ws->cx = 0;
	ws->cy = 0;
	ws->ax = -0.1011;
	ws->ay = 0.9563;
	ws->scale = 0.005;
	ws->decincvar = 50;
	ws->maxiterations = 200;
	ws->col_type = 0;
	ws->mmotion = 0;
	ws->type = 2;
	ws->colors = (int*)malloc(sizeof(int) * ws->maxiterations);
	ws->base_color = 0x2E8B57;
	ft_makecolors(ws->maxiterations, ws->colors, ws->base_color);
}

void	ft_drawnixel(t_wnd *ws, int x, int y)
{
	int	i;

	i = 0;
	while (i < ws->maxiterations &&
			((ws->a1 * ws->a1) + (ws->b1 * ws->b1)) < (1 << 16))
	{
		i++;
		ws->a2 = ws->a1 * ws->a1 * ws->a1 - 3 *
			ws->a1 * ws->b1 * ws->b1 + ws->ax;
		ws->b2 = 3 * ws->a1 * ws->a1 * ws->b1 -
			ws->b1 * ws->b1 * ws->b1 + ws->ay;
		ws->a1 = ws->a2;
		ws->b1 = ws->b2;
	}
	ft_getcolor(x, y, i, ws);
}

int		ft_drawnset(void *vws)
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
			ft_drawnixel(ws, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(ws->mlx, ws->win, ws->image, 0, 0);
	mlx_destroy_image(ws->mlx, ws->image);
	ft_showinfo(ws);
	return (0);
}

int		ft_mactionn(int x, int y, t_wnd *ws)
{
	static int	prevx;
	static int	prevy;
	float		var;

	if (x >= 0 && y >= 0 && x <= ws->width &&
			y <= ws->height && ws->mmotion == 1)
	{
		if (abs((prevx + prevy) - (x + y)) > 25)
		{
			prevx = x;
			prevy = y;
			var = ((float)rand() / (float)(RAND_MAX)) * 2;
			ws->ax = 0.7885 * cos(var);
			ws->ay = 0.7885 * sin(var);
			ft_drawnset(ws);
		}
	}
	return (0);
}
