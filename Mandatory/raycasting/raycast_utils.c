/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 04:49:15 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 20:49:57 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_data *d, t_ray *r, int map_x, int map_y)
{
	if (r->dir[0] < 0)
	{
		r->step_x = -1;
		r->x_len = (d->pos[0] - map_x) * r->dx;
	}
	else
	{
		r->step_x = 1;
		r->x_len = (map_x - d->pos[0] + 1) * r->dx;
	}
	if (r->dir[1] < 0)
	{
		r->step_y = -1;
		r->y_len = (d->pos[1] - map_y) * r->dy;
	}
	else
	{
		r->step_y = 1;
		r->y_len = (map_y - d->pos[1] + 1) * r->dy;
	}
}

void	raycaster(t_data *d, t_ray *r)
{
	int	map_x;
	int	map_y;

	map_x = d->pos[0];
	map_y = d->pos[1];
	init_ray(d, r, map_x, map_y);
	while (1)
	{
		if (r->x_len < r->y_len)
		{
			r->len = r->x_len;
			r->x_len += r->dx;
			map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->len = r->y_len;
			r->y_len += r->dy;
			map_y += r->step_y;
			r->side = 1;
		}
		if (d->map->v[map_y][map_x] == '1')
			break ;
	}
}
