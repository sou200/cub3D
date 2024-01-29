/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 04:50:46 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/29 01:53:26 by serhouni         ###   ########.fr       */
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
