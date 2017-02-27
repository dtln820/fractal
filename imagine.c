#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void *mlx;
void *win;
void *image;
void *img;

char *im_buf;
int bits;
int sizel;
int endi;

void put_pixel(int x, int y, int color)
{
  int i;

  i = x * bits / 8 + y * sizel;
  im_buf[i] = color & 0xFF;
  im_buf[i + 1] = (color & 0xFF00) >> 8;
  im_buf[i + 2] = (color & 0xFF0000) >> 16;
}

int main()
{
  mlx = mlx_init();
  win = mlx_new_window(mlx, 800, 600, "Testing images");
  image = mlx_new_image(mlx, 800, 600);
  im_buf = mlx_get_data_addr(image, &bits, &sizel, &endi);
  for (int i = 0; i < 800; i++)
  {
    for (int j = 0; j < 600; j++)
    {
      if ((i + j) / 2 == 0)
        put_pixel(i, j, 000000000);
      else
        put_pixel(i, j, i * 255 * j);
    }
  }
  mlx_put_image_to_window(mlx, win, image, 0, 0);
  mlx_loop(mlx);
  return 0;
}
