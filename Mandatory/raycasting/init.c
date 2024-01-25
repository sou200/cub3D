/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:49:39 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 07:59:17 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_data *d, t_args *args)
{
	set_vector(d->pos, args->x, args->y);
	set_vector(d->dir, 0, 1);
	set_vector(d->plan, -0.66, 0);
	if (args->dir == 'W')
		player_rotate(d, M_PI_2);
	else if (args->dir == 'E')
		player_rotate(d, -M_PI_2);
	else if (args->dir == 'N')
		player_rotate(d, M_PI);
}

void	init_textures(t_data *data, t_args *args)
{
	t_textures	*texs;

	texs = m_malloc(sizeof(t_textures));
	if (!texs)
		terminate(data, EXIT_FAILURE, args, 1);
	texs->no_tex = mlx_load_png(args->no);
	texs->so_tex = mlx_load_png(args->so);
	texs->we_tex = mlx_load_png(args->we);
	texs->ea_tex = mlx_load_png(args->ea);
	data->texs = texs;
	if (!texs->no_tex || !texs->so_tex || !texs->we_tex || !texs->ea_tex)
		terminate(data, EXIT_FAILURE, args, 1);
}

void	init_minimap(t_data *d, t_args *args)
{
	d->minimap = m_malloc(sizeof(t_minimap));
	if (!d->minimap)
		terminate(d, EXIT_FAILURE, args, 1);
	d->minimap->size = 100;
	d->minimap->x = 20;
	d->minimap->y = 20;
	d->minimap->zoom = 0.05;
}

void	init_map(t_data *d, t_args *args)
{
	d->map = m_malloc(sizeof(t_map));
	if (!d->map)
		terminate(d, EXIT_FAILURE, args, 1);
	d->map->v = args->map;
	d->map->w = args->w;
	d->map->h = args->h;
}

t_data	*game_init(int ac, char **av)
{
	t_args	*args;
	t_data	*d;

	args = parsing(ac, av);
	d = m_malloc(sizeof(t_data));
	if (!d)
		return (terminate(d, EXIT_FAILURE, args, 1), NULL);
	d->f_color = rgbt(args->f_colors[0], args->f_colors[1], args->f_colors[2],
			0xff);
	d->c_color = rgbt(args->c_colors[0], args->c_colors[1], args->c_colors[2],
			0xff);
	d->mlx = my_mlx_init(WIDTH, HIGHT, "cub3d");
	if (!d->mlx)
		return (terminate(d, EXIT_FAILURE, args, 1), NULL);
	d->image = NULL;
	mlx_get_mouse_pos(d->mlx, &d->mouse_x, NULL);
	init_player(d, args);
	init_map(d, args);
	init_textures(d, args);
	init_minimap(d, args);
	init_animation(d, args);
	free_args(args, 0);
	return (d);
}
