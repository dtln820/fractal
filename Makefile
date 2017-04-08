CC = gcc
CFLAGS = -Werror -Wall -Wextra
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
NAME = fractol

$(NAME): ft_common.o ft_common2.o ft_help.o brot.o newton.o set_julia.o main.o
	$(CC) $(CFLAGS) ft_common.o ft_common2.o ft_help.o brot.o newton.o set_julia.o main.o -o fractol $(MLXFLAGS)

all: $(NAME)

ft_common.o: ft_common.c b_fractal.h
	$(CC) $(CFLAGS) -c ft_common.c -o ft_common.o

ft_common2.o: ft_common2.c b_fractal.h
	$(CC) $(CFLAGS) -c ft_common2.c -o ft_common2.o

ft_help.o: ft_help.c b_fractal.h
	$(CC) $(CFLAGS) -c ft_help.c -o ft_help.o

brot.o: brot.c b_fractal.h
	$(CC) $(CFLAGS) -c brot.c -o brot.o

newton.o: newton.c b_fractal.h
	$(CC) $(CFLAGS) -c newton.c -o newton.o

set_julia.o: set_julia.c b_fractal.h
	$(CC) $(CFLAGS) -c set_julia.c -o set_julia.o

main.o: main.c b_fractal.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f ft_common.o ft_common2.o ft_help.o brot.o newton.o set_julia.o main.o

fclean: clean
	rm -f $(NAME)

re: fclean all
