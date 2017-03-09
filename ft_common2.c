/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_common2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddulgher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 12:05:57 by ddulgher          #+#    #+#             */
/*   Updated: 2017/03/04 13:28:58 by ddulgher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_fractal.h"

void	ft_makecolors(int max, int *colors, int basecolor)
{
	int	i;

	i = 0;
	while (i < max)
	{
		colors[i] = basecolor + i * 10;
		i++;
	}
}

void	ft_putpixel(t_wnd *ws, int x, int y, int color)
{
	int	i;

	i = x * ws->bits / 8 + y * ws->sizel;
	ws->im_buf[i] = color & 0xFF;
	ws->im_buf[i + 1] = (color & 0xFF00) >> 8;
	ws->im_buf[i + 2] = (color & 0xFF0000) >> 16;
}

int		ft_return(t_wnd *ws)
{
	if (ws->type == 0)
		return (ft_drawmset(ws));
	else if (ws->type == 1)
		return (ft_drawjset(ws));
	else if (ws->type == 2)
		return (ft_drawnset(ws));
	else
		return (0);
}

int		key_hook3(int k, t_wnd *ws)
{
	if (k == 123)
	{
		ws->cx++;
		return (ft_return(ws));
	}
	else if (k == 124)
	{
		ws->cx--;
		return (ft_return(ws));
	}
	else if (k == 126)
	{
		ws->cy++;
		return (ft_return(ws));
	}
	else if (k == 125)
	{
		ws->cy--;
		return (ft_return(ws));
	}
	return (0);
}
