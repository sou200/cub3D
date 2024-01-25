#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "parsing/cub3d1.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HIGHT 600
# define M_VOL 0.08
# define R_VOL 0.03

// int map[5][8] = {
//             {1,1,1,1,1,1,1,1},
//             {1,0,0,0,0,0,0,1},
//             {1,0,1,1,0,0,0,1},
//             {1,0,0,0,0,0,0,1},
//             {1,1,1,1,1,1,1,1}
//             };
// extern int map[16][20];

typedef double		t_dbl;

typedef struct s_minimap
{
	int				x;
	int				y;
	int				size;
	t_dbl			zoom;
	t_dbl			px;
	t_dbl			py;
}					t_minimap;

typedef struct s_anim
{
	int				i;
	mlx_texture_t	*frames[45];
	int				anim_state;
	int				n;
	unsigned int	s_x;
	unsigned int	s_y;
}					t_anim;

typedef struct s_textures
{
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	mlx_texture_t	*no_tex;
}					t_textures;

typedef struct s_map
{
	char			**v;
	int				w;
	int				h;
}					t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_dbl			pos[2];
	t_dbl			dir[2];
	t_dbl			plan[2];
	mlx_texture_t	*t;
	int				mouse_x;
	int				f_color;
	int				c_color;
	t_map			*map;
	t_textures		*texs;
	t_anim			*anim;
	t_minimap		*minimap;
}					t_data;

// typedef struct s_args
// {
// char *no;
// char *so;
// char *we;
// char *ea;
// int f_colors[3];
// int c_colors[3];
// double x;
// double y;
// char dir;
// int p;
// char **map;
// } t_args;

typedef struct s_ray
{
	t_dbl			dir[2];
	t_dbl			len;
	double			dx;
	double			dy;
	int				side;
	int				stepX;
	int				stepY;
	double			x_len;
	double			y_len;
}					t_ray;

enum				player_state
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_RIGHT,
	MOVE_LEFT,
	ROT_RIGHT,
	ROT_LEFT
};

void				render_map(t_data *d);
int					draw_line_p(t_data *d, int endX, int endY);
void				player_rotate_key(t_data *data, enum player_state state);
void				player_rotate(t_data *data, t_dbl alpha);
void				player_move(t_data *data, enum player_state state);
int					get_factor(enum player_state state);
void				rotate_vector(t_dbl *vec, t_dbl a);
void				set_vector(t_dbl *vec, t_dbl x, t_dbl y);
void				vector_unit(t_dbl *vec);
void				rotate_vector(t_dbl *vec, t_dbl a);
void				key_hook(void *param);
t_data				*game_init(int ac, char **av);
void				mouse_key_hook(mouse_key_t button, action_t action,
						modifier_key_t mods, void *param);
void				mouse_loop(void *param);
void				draw_minimap_border(t_data *d, int color);
int					rgbt(int r, int g, int b, int t);
void				weapon_anim(t_data *data);
void				free_data(t_data *data);
void				free_args(t_args *args, int free_map_f);
void				*ft_memset(void *s, int c, size_t n);
void				*m_malloc(size_t size);
void				terminate(t_data *data, int exit_status, t_args *args,
						int free_args_f);
mlx_t				*my_mlx_init(int32_t width, int32_t height,
						const char *title);
void				my_mlx_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
						uint32_t color);
void				render_floor_celling(t_data *data);
void				raycaster(t_data *d, t_ray *r);
void				close_hook(void *param);
void				init_animation(t_data *d, t_args *args);

#endif