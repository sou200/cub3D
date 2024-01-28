/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:48:13 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/28 09:28:28 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_strip_tex(t_data *d, t_ray ray, double *offset)
{
	if (ray.side)
	{
		*offset = d->pos[0] + ray.dir[0] * ray.len;
		if (ray.dir[1] > 0)
			d->t = d->texs->no_tex;
		else
			d->t = d->texs->so_tex;
	}
	else
	{
		*offset = d->pos[1] + ray.dir[1] * ray.len;
		if (ray.dir[0] > 0)
			d->t = d->texs->ea_tex;
		else
			d->t = d->texs->we_tex;
	}
}

void	border_wall(int *beg, int *end, double *text_y, double step)
{
	if (*end > HIGHT)
		*end = HIGHT;
	if (*beg < 0)
	{
		*text_y = -(*beg * step);
		*beg = 0;
	}
}

void	render_textures(t_data *d, t_ray ray, int wall_height, int beg)
{
	double	offset;
	double	text_y;
	double	step;
	int		end;

	end = beg + wall_height;
	init_strip_tex(d, ray, &offset);
	offset -= floor(offset);
	text_y = 0;
	step = (t_dbl)d->t->height / wall_height;
	border_wall(&beg, &end, &text_y, step);
	while (beg < end)
	{
		ray.pixel = d->t->pixels + ((int)text_y * d->t->width + (int)(offset
					* d->t->width)) * d->t->bytes_per_pixel;
		my_mlx_put_pixel(d->image, ray.index, beg, rgbt(ray.pixel[0],
				ray.pixel[1], ray.pixel[2], ray.pixel[3]));
		text_y += step;
		beg++;
	}
}

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
