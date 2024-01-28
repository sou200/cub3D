/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:38:04 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 23:49:24 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_minimap_border(t_data *d, int color)
{
	int	i;
	int	j;

	i = d->minimap->x;
	j = d->minimap->y;
	while (i <= d->minimap->size + d->minimap->x)
	{
		my_mlx_put_pixel(d->image, i, d->minimap->y, color);
		my_mlx_put_pixel(d->image, i, d->minimap->y + d->minimap->size, color);
		i++;
	}
	while (j <= d->minimap->size + d->minimap->y)
	{
		my_mlx_put_pixel(d->image, d->minimap->x, j, color);
		my_mlx_put_pixel(d->image, d->minimap->x + d->minimap->size, j, color);
		j++;
	}
}

void	init_line_p(double *delta_x, double *delta_y, int *pixels)
{
	*pixels = sqrt((*delta_x * *delta_x) + (*delta_y * *delta_y));
	*delta_x /= *pixels;
	*delta_y /= *pixels;
}

int	draw_line_p(t_data *d, int endX, int endY)
{
	double	delta_x;
	double	delta_y;
	int		pixels;

	delta_x = endX - d->minimap->px;
	delta_y = endY - d->minimap->py;
	init_line_p(&delta_x, &delta_y, &pixels);
	while (pixels)
	{
		my_mlx_put_pixel(d->image, d->minimap->px, d->minimap->py, rgbt(255, 40,
				40, 255));
		d->minimap->px += delta_x;
		d->minimap->py += delta_y;
		--pixels;
	}
	return (1);
}
