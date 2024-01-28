/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:48:13 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/27 04:15:56 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_game(t_data *d)
{
	t_ray			ray;
	t_dbl			cam;
	int				wall_height;
	int				beg;
	int				end;
	t_dbl			offset;
	int				textX;
	t_dbl			textY;
	t_dbl			step;
	int				j;
	unsigned char	*pixel;

	for (int i = 0; i < WIDTH; i++)
	{
		cam = (2.0 * i) / WIDTH - 1;
		set_vector(ray.dir, d->dir[0] + d->plan[0] * cam, d->dir[1] + d->plan[1]
			* cam);
		ray.dx = (ray.dir[0] == 0) ? MAXFLOAT : fabs(1 / ray.dir[0]);
		ray.dy = (ray.dir[1] == 0) ? MAXFLOAT : fabs(1 / ray.dir[1]);
		raycaster(d, &ray);
		wall_height = (HIGHT / ray.len);
		beg = (HIGHT - wall_height) / 2;
		end = beg + wall_height;
		// TODO: textures.
		if (ray.side)
		{
			offset = d->pos[0] + ray.dir[0] * ray.len;
			if (ray.dir[1] > 0)
				d->t = d->texs->we_tex;
			else
				d->t = d->texs->ea_tex;
		}
		else
		{
			offset = d->pos[1] + ray.dir[1] * ray.len;
			if (ray.dir[0] > 0)
				d->t = d->texs->no_tex;
			else
				d->t = d->texs->so_tex;
		}
		offset -= floor(offset);
		textX = offset * d->t->width;
		textY = 0;
		step = (t_dbl)d->t->height / wall_height;
		if(end > HIGHT)
		    end = HIGHT;
		if(beg < 0)
		{
		    textY = -(beg * step);
		    beg = 0;
		}
		j = beg;
		while (j < end)
		{
			pixel = d->t->pixels + ((int)textY * d->t->width + (int)textX)
				* d->t->bytes_per_pixel;
			my_mlx_put_pixel(d->image, i, j, rgbt(pixel[0], pixel[1], pixel[2],
					pixel[3]));
			textY += step;
			j++;
		}
		// textures end.
		// draw_line(d->image, i, beg, i, end);
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
	weapon_anim(data);
	if (data->anim->anim_state && data->anim->i >= 45)
	{
		data->anim->i = 0;
		data->anim->anim_state = 0;
	}
	render_map(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
