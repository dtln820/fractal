#include "b_fractal.h"

int main(int argc, char *argv[])
{
	t_wnd *ws;

  if (argc < 2)
  {
    printf("Usage: ./fractol filename\n");
    return (0);
  }
  ws = malloc(sizeof(t_wnd));
  if (ft_strcmp(argv[1], "Mandelbrot") == 0)
  {
    ft_fillm(ws);
    mlx_expose_hook(ws->win, &ft_drawmset, ws);
    mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mactionb, ws);
  }
  else if (ft_strcmp(argv[1], "Julia") == 0)
  {
    ft_fillj(ws);
    mlx_expose_hook(ws->win, &ft_drawjset, ws);
    mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mactionj, ws);
  }
  else if (ft_strcmp(argv[1], "Random") == 0)
  {
    ft_filln(ws);
    mlx_expose_hook(ws->win, &ft_drawnset, ws);
    mlx_hook(ws->win, MOTION_NOTIFY, PTR_MOTION_MASK, &ft_mactionn, ws);
  }
	mlx_key_hook(ws->win, &key_hook, ws);
	mlx_mouse_hook(ws->win, &mouse_hook, ws);
	mlx_loop(ws->mlx);
	return 0;
}
