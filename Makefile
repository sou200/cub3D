NAME = cub3d
B_NAME = cub3d_bonus
CFLAGS =  -Werror -Wextra -Wall #-fsanitize=address -g3
RM = rm -f
CC = cc
MLXFLAGS = -Iinclude -lglfw -L"/Users/${USER}/homebrew/opt/glfw/lib/"
MLXLIB = MLX42/libmlx42.a

SRCS = Mandatory/main.c \
	Mandatory/raycasting/player_events.c \
	Mandatory/raycasting/vector_utils.c \
	Mandatory/raycasting/key_handler.c \
	Mandatory/raycasting/init.c \
	Mandatory/raycasting/color_utils.c \
	Mandatory/raycasting/free_utils.c \
	Mandatory/raycasting/free_data.c \
	Mandatory/raycasting/lib_utils.c \
	Mandatory/raycasting/better_mlx.c \
	Mandatory/raycasting/floor_celling.c \
	Mandatory/raycasting/raycast_utils.c \
	Mandatory/raycasting/textures.c \
	Mandatory/raycasting/game_hook.c \
	Mandatory/parsing/gnl.c \
	Mandatory/parsing/gnl1.c \
	Mandatory/parsing/pars.c \
	Mandatory/parsing/pars1.c \
	Mandatory/parsing/pars2.c \
	Mandatory/parsing/pars3.c \
	Mandatory/parsing/pars4.c \
	Mandatory/parsing/pars5.c \
	Mandatory/parsing/pars6.c \
	Mandatory/parsing/lib.c \


B_SRCS = Bonus/main.c \
	Bonus/raycasting/player_events.c \
	Bonus/raycasting/vector_utils.c \
	Bonus/raycasting/key_handler.c \
	Bonus/raycasting/init.c \
	Bonus/raycasting/mouse_handler.c \
	Bonus/raycasting/draw_utils.c \
	Bonus/raycasting/map_rendring.c \
	Bonus/raycasting/color_utils.c \
	Bonus/raycasting/animation.c \
	Bonus/raycasting/free_utils.c \
	Bonus/raycasting/free_data.c \
	Bonus/raycasting/lib_utils.c \
	Bonus/raycasting/better_mlx.c \
	Bonus/raycasting/floor_celling.c \
	Bonus/raycasting/raycast_utils.c \
	Bonus/raycasting/textures.c \
	Bonus/raycasting/init_anim.c \
	Bonus/raycasting/game_hook.c \
	Bonus/parsing/gnl.c \
	Bonus/parsing/gnl1.c \
	Bonus/parsing/pars.c \
	Bonus/parsing/pars1.c \
	Bonus/parsing/pars2.c \
	Bonus/parsing/pars3.c \
	Bonus/parsing/pars4.c \
	Bonus/parsing/pars5.c \
	Bonus/parsing/pars6.c \
	Bonus/parsing/lib.c \



OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(MLXLIB) $^ -o $@

%.o : %.c Mandatory/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus : $(B_OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(MLXLIB) $^ -o $(B_NAME)

clean :
	$(RM) $(OBJS)
	$(RM) $(B_OBJS)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(B_NAME)

re : fclean all