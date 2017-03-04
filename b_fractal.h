/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_fractal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddulgher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 11:30:51 by ddulgher          #+#    #+#             */
/*   Updated: 2017/03/04 13:29:12 by ddulgher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_FRACTAL_H
# define B_FRACTAL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

typedef	struct		s_wnd
{
	int				maxiterations;
	int				width;
	int				type;
	int				height;
	int				col_type;
	int				mmotion;
	void			*mlx;
	void			*win;
	void			*image;
	int				bits;
	int				sizel;
	int				endi;
	char			*im_buf;
	long double		cx;
	long double		cy;
	long double		scale;
	long double		a1;
	long double		b1;
	long double		a2;
	long double		b2;
	long double		ax;
	long double		ay;
	int				decincvar;
	int				*colors;
}					t_wnd;

void				ft_makecolors(int max, int *colors);

void				ft_putpixel(t_wnd *ws, int x, int y, int color);

int					ft_showinfo(t_wnd *ws);

void				ft_getcolor(int x, int y, int i, t_wnd *ws);

int					mouse_hook(int button, int x, int y, void *vws);

int					key_hook2(int k, t_wnd *ws);

int					key_hook(int k, void *vws);

int					ft_mactionn(int x, int y, t_wnd *ws);

int					ft_drawnset(void *vws);

void				ft_drawnixel(t_wnd *ws, int x, int y);

void				ft_filln(t_wnd *ws);

void				ft_fillj(t_wnd *ws);

void				ft_drawjixel(t_wnd *ws, int x, int y);

int					ft_drawjset(void *vws);

int					ft_mactionj(int x, int y, t_wnd *ws);

void				ft_fillm(t_wnd *ws);

void				ft_drawmixel(t_wnd *ws, int x, int y);

int					ft_drawmset(void *vws);

int					ft_mactionb(int x, int y, t_wnd *ws);

void				ft_putstr(char const *s);

int					ft_strcmp(const char *str1, const char *str2);

int					ft_initfrac(char *path, t_wnd *ws);

int					ft_return(t_wnd *ws);

#endif
