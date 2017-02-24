#ifndef A_FRACTAL_H
# define A_FRACTAL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <time.h>

typedef struct    s_wnd
{
  void *mlx;
  void *win;
  int height;
  int width;
  int max;
  double moveX;
  double moveY;
  int *colors;
  double zoom;
  int prevx;
  int prevy;
}                 t_wnd;

#endif
