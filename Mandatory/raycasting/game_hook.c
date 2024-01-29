/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:48:13 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/29 01:50:38 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_slop(t_ray *ray)
{
	if (ray->dir[0] == 0)
		ray->dx = MAXFLOAT;
	else
		ray->dx = fabs(1 / ray->dir[0]);
	if (ray->dir[1] == 0)
		ray->dy = MAXFLOAT;
	else
		ray->dy = fabs(1 / ray->dir[1]);
}

void	render_game(t_data *d)
{
	t_ray	ray;
	t_dbl	cam;
	int		wall_height;
	int		beg;

	ray.index = 0;
	while (ray.index < WIDTH)
	{
		cam = (2.0 * ray.index) / WIDTH - 1;
		set_vector(ray.dir, d->dir[0] + d->plan[0] * cam, d->dir[1] + d->plan[1]
			* cam);
		set_slop(&ray);
		raycaster(d, &ray);
		wall_height = (HIGHT / ray.len);
		beg = (HIGHT - wall_height) / 2;
		render_textures(d, ray, wall_height, beg);
		ray.index++;
	}
}

void	game_loop(void *g)
{
	t_data	*data;

	data = (t_data *)g;
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, WIDTH);
	render_floor_celling(data);
	render_game(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
