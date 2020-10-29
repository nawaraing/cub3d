NAME = cub3d
CC = GCC
CFLAGS = -Wall -Wextra -Werror
INCL = cub3d.h gnl/get_next_line.h
SRCS = $(addprefix engine/, main.c put_image.c background.c sprite.c dda.c init.c parse_file.c parse_render_sprite.c valid_map.c parse_map.c parse_nsew.c parse_floor_ceil.c hook.c screenshot.c move.c libft.c utils.c ) \
		gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

LIBS = -framework OpenGL -framework AppKit

MLX = libmlx.a

all : $(NAME)

$(NAME) : $(MLX) $(OBJS)
	    $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(MLX) -I.

$(MLX) :
	    @$(MAKE) -C mlx
	    @mv mlx/$(MLX) .

clean :
	    @$(MAKE) -C mlx clean
	    rm -f $(OBJS) $(BONUS_OBJS)

fclean :    clean
	    rm -f $(NAME) $(MLX)

re : fclean all
