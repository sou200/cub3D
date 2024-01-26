NAME = cub3d
CFLAGS =  -Werror -Wextra -Wall #-fsanitize=address -g3
RM = rm -f
CC = cc
MLXFLAGS = -Iinclude -lglfw -L"/Users/${USER}/.brew/opt/glfw/lib/"
MLXLIB = MLX42/build/libmlx42.a

SRCS = Mandatory/main.c \
	Mandatory/raycasting/player_events.c \
	Mandatory/raycasting/vector_utils.c \
	Mandatory/raycasting/key_handler.c \
	Mandatory/raycasting/init.c \
	Mandatory/raycasting/mouse_handler.c \
	Mandatory/raycasting/draw_utils.c \
	Mandatory/raycasting/map_rendring.c \
	Mandatory/raycasting/color_utils.c \
	Mandatory/raycasting/animation.c \
	Mandatory/raycasting/free_utils.c \
	Mandatory/raycasting/free_data.c \
	Mandatory/raycasting/lib_utils.c \
	Mandatory/raycasting/better_mlx.c \
	Mandatory/raycasting/floor_celling.c \
	Mandatory/raycasting/raycast_utils.c \
	Mandatory/raycasting/textures.c \
	Mandatory/raycasting/init_anim.c \
	Mandatory/raycasting/game_hook.c \
	Mandatory/parsing/gnl.c \
	Mandatory/parsing/parc.c \



OBJS = $(SRCS:.c=.o)

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(MLXLIB) $^ -o $@

%.o : %.c Mandatory/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all