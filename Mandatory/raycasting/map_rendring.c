/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:45:54 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/26 03:35:44 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	in_map_bound(t_map *m, int x, int y)
{
	return (x >= 0 && y >= 0 && x < m->w && y < m->h);
}

void	draw_player(t_data *d)
{
	int	end_x;
	int	end_y;

	d->minimap->px = (d->minimap->size / 2) + d->minimap->x;
	d->minimap->py = (d->minimap->size / 2) + d->minimap->y;
	end_x = d->minimap->px + d->dir[0] / d->minimap->zoom;
	end_y = d->minimap->py + d->dir[1] / d->minimap->zoom;
	if (end_x < d->minimap->x)
		end_x = d->minimap->x;
	else if (end_x > d->minimap->size + d->minimap->x)
		end_x = d->minimap->size + d->minimap->x;
	if (end_y < d->minimap->y)
		end_y = d->minimap->y;
	else if (end_y > d->minimap->size + d->minimap->y)
		end_y = d->minimap->size + d->minimap->y;
	draw_line_p(d, end_x, end_y);
}

int	get_map_pixel_color(t_data *d, int mx, int my)
{
	int	color;

	if (in_map_bound(d->map, mx, my) && d->map->v[my][mx] == '0')
		color = rgbt(190, 190, 190, 255);
	else if (in_map_bound(d->map, mx, my) && d->map->v[my][mx] == '1')
		color = rgbt(150, 75, 0, 255);
	else
		color = rgbt(50, 50, 50, 255);
	return (color);
}

void	render_map(t_data *d)
{
	int	j;
	int	i;
	int	mx;
	int	my;

	j = 0;
	while (j < d->minimap->size)
	{
		i = 0;
		while (i < d->minimap->size)
		{
			mx = (int)(d->pos[0] + d->minimap->zoom * i - (d->minimap->zoom
						* d->minimap->size) / 2);
			my = (int)(d->pos[1] + d->minimap->zoom * j - (d->minimap->zoom
						* d->minimap->size) / 2);
			my_mlx_put_pixel(d->image, i + d->minimap->x, j + d->minimap->y,
				get_map_pixel_color(d, mx, my));
			i++;
		}
		j++;
	}
	draw_player(d);
	draw_minimap_border(d, rgbt(255, 255, 255, 255));
}
