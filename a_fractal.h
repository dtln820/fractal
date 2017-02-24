#ifndef A_FRACTAL_H
# define A_FRACTAL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct    s_wnd
{
  void *mlx;
  void *win;
  int height;
  int width;
  int max;
  int limit;
  int cx;
  int cy;
  int *colors;
  double scale;
}                 t_wnd;

#endif
