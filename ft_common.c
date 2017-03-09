/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_common.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddulgher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:45:11 by ddulgher          #+#    #+#             */
/*   Updated: 2017/03/04 13:28:51 by ddulgher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_fractal.h"

int		ft_showinfo(t_wnd *ws)
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
	return (0);
}

void	ft_getcolor(int x, int y, int i, t_wnd *ws)
{
	if (i >= ws->maxiterations)
		ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, 0x000000);
	else if (ws->col_type == 0)
		ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, i % 256);
	else
		ft_putpixel(ws, x + ws->width / 2, y + ws->height / 2, ws->colors[i]);
}

int		mouse_hook(int button, int x, int y, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	if (button == 4)
	{
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale / 2;
		return (ft_return(ws));
	}
	else if (button == 5)
	{
		ws->cx = ws->cx + ws->scale * (x - (ws->width / 2));
		ws->cy = ws->cy + ws->scale * (y - (ws->height / 2));
		ws->scale = ws->scale * 2;
		return (ft_return(ws));
	}
	return (0);
}

int		key_hook2(int k, t_wnd *ws)
{
	if (k == 53)
		exit(1);
	else if (k == 17)
	{
		if (ws->col_type == 0)
			ws->col_type = 1;
		else
			ws->col_type = 0;
		return (ft_return(ws));
	}
	else if (k == 46)
	{
		if (ws->mmotion == 0)
			ws->mmotion = 1;
		else
			ws->mmotion = 0;
		return (ft_return(ws));
	}
	else
		return (0);
}

int		key_hook(int k, void *vws)
{
	t_wnd *ws;

	ws = (t_wnd*)vws;
	if (k == 12)
	{
		ws->maxiterations += ws->decincvar;
		if (ws->maxiterations >= 100)
			ws->decincvar = 50;
		free(ws->colors);
		ws->colors = (int*)malloc(sizeof(int) * ws->maxiterations);
		ft_makecolors(ws->maxiterations, ws->colors, ws->base_color);
		return (ft_return(ws));
	}
	else if (k == 14)
	{
		ws->maxiterations -= ws->decincvar;
		if (ws->maxiterations <= 100)
			ws->decincvar = 10;
		free(ws->colors);
		ws->colors = (int*)malloc(sizeof(int) * ws->maxiterations);
		ft_makecolors(ws->maxiterations, ws->colors, ws->base_color);
		return (ft_return(ws));
	}
	else
		return (key_hook2(k, ws));
}
