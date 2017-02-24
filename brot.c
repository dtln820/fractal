#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void *mlx;
void *win;

void ft_makecolors(int max, int *colors)
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

int main()
{
  int lp;
  double scale;
  double limit;
  int colors[1000];
  ft_makecolors(1000, colors);
  mlx = mlx_init();
  win = mlx_new_window(mlx, 800, 600, "Test");
  double ax, ay, a1, b1, a2, b2;
  limit = 20;
  scale = 0.005;
  for (int x = -400; x < 399; x++)
  {
    for (int y = -300; y < 299; y++)
    {
      ax = x * scale;
      ay = y * scale;
      a1 = ax;
      b1 = ay;
      lp = 0;

      while (lp <= 1000 && ((a1 * a1) + (b1 * b1)) < limit)
      {
        a2 = a1 * a1 - b1 * b1 + ax;
        b2 = 2 * a1 * b1 + ay;
        a1 = a2;
        b1 = b2;
        lp++;
      }
      if (lp > 1000)
        mlx_pixel_put(mlx, win, x + 400, y + 300, 0x000000);
      else
        mlx_pixel_put(mlx, win, x + 400, y + 300, colors[lp]);
    }
  }
  mlx_loop(mlx);
  return 0;
}
