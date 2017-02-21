#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void *mlx;
void *win;

void ft_makecolors(int max, int colors[])
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

int   main(int argc, char *argv[])
{
  int height, width;
  int max;

  max = 100;
  height = 480;
  width = 640;
  int colors[max];
  ft_makecolors(max, colors);
  mlx = mlx_init();
  win = mlx_new_window(mlx, width, height, "Fractal");
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      double c_re = (col - width / 2.0) * 4.0 / width;
      double c_im = (row - height / 2.0) * 4.0 / width;
      double x = 0;
      double y = 0;
      int iteration = 0;
      while (x * x + y * y <= 4 && iteration < max)
      {
        double x_new = x * x - y * y + c_re;
        y = 2 * x * y + c_im;
        x = x_new;
        iteration++;
      }
      if (iteration < max)
        mlx_pixel_put(mlx, win, col, row, colors[iteration]);
      else
        mlx_pixel_put(mlx, win, col, row, 0x000000);
    }
  }
  mlx_loop(mlx);
  return (0);
}
