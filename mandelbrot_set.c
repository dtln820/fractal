#include "a_fractal.h"

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

int ft_drawmset(void *vws)
{
  t_wnd *ws;

  ws = (t_wnd*)vws;
  mlx_clear_window(ws->mlx, ws->win);
  for (int row = 0; row < ws->height; row++)
  {
    for (int col = 0; col < ws->width; col++)
    {
      double c_re = (col - ws->cx / 2) * ws->scale / ws->width;
      double c_im = (row - ws->cy / 2) * ws->scale / ws->width;
      double x = 0;
      double y = 0;
      int iteration = 0;
      while (x * x + y * y <= ws->limit && iteration < ws->max)
      {
        double x_new = x * x - y * y + c_re;
        y = 2 * x * y + c_im;
        x = x_new;
        iteration++;
      }
      if (iteration < ws->max)
        mlx_pixel_put(ws->mlx, ws->win, col, row, ws->colors[iteration]);
      else
        mlx_pixel_put(ws->mlx, ws->win, col, row, 0x000000);
    }
  }
  return 0;
}

void ft_fillstruct(t_wnd *ws)
{
  ws->limit = 4;
  ws->scale = 4.0;
  ws->width = 800;
  ws->height = 600;
  ws->cx = ws->width;
  ws->cy = ws->height;
  ws->mlx = mlx_init();
  ws->win = mlx_new_window(ws->mlx, ws->width, ws->height, "Fractal");
  ws->max = 50;
  ws->colors = (int*)malloc(sizeof(int) * ws->max);
  ft_makecolors(ws->max, ws->colors);
}

int key_hook(int k, void *vws)
{
  t_wnd *ws;

  ws = (t_wnd*)vws;
  if (k == 53)
    exit(1);
  else
  {
    printf("k == %d\n", k);
    return (0);
  }
  return (ft_drawmset(ws));
}

int mouse_hook(int button, int x, int y, void *vws)
{
  t_wnd *ws;

  ws = (t_wnd*)vws;
  printf("button = %d\n", button);
  printf("x = %d y = %d\n", x, y);
  if (button == 1)
  {
    ws->scale = ws->scale / 2;
    ws->cx = x;
    ws->cy = y;
  }
  else if (button == 2)
  {
    ws->scale = ws->scale * 2;
    ws->cx = x;
    ws->cy = y;
  }
  else
    return 0;
  return (ft_drawmset(ws));
}

int main(int argc, char *argv[])
{
  t_wnd *ws;
  ws = malloc(sizeof(t_wnd));
  ft_fillstruct(ws);
  ft_drawmset(ws);
  mlx_key_hook(ws->win, &key_hook, ws);
  mlx_mouse_hook(ws->win, &mouse_hook, ws);
  mlx_expose_hook(ws->win, &ft_drawmset, ws);
  mlx_loop(ws->mlx);
  return (0);
}
