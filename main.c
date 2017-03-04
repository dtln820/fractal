/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddulgher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 12:09:52 by ddulgher          #+#    #+#             */
/*   Updated: 2017/03/04 12:19:47 by ddulgher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_fractal.h"

int		ft_initfrac(char *path, t_wnd *ws)
{
	if (ft_strcmp(path, "Mandelbrot") == 0)
	{
		ft_fillm(ws);
		mlx_expose_hook(ws->win, &ft_drawmset, ws);
		mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mactionb, ws);
	}
	else if (ft_strcmp(path, "Julia") == 0)
	{
		ft_fillj(ws);
		mlx_expose_hook(ws->win, &ft_drawjset, ws);
		mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mactionj, ws);
	}
	else if (ft_strcmp(path, "Random") == 0)
	{
		ft_filln(ws);
		mlx_expose_hook(ws->win, &ft_drawnset, ws);
		mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mactionn, ws);
	}
	else
	{
		ft_putstr("Error, wrong type!\n");
		return (-1);
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_wnd *ws;

	if (argc < 2)
	{
		printf("Usage: ./fractol filename\n");
		return (0);
	}
	ws = malloc(sizeof(t_wnd));
	if (ft_initfrac(argv[1], ws) == -1)
		return (0);
	mlx_key_hook(ws->win, &key_hook, ws);
	mlx_mouse_hook(ws->win, &mouse_hook, ws);
	mlx_loop(ws->mlx);
	return (0);
}
