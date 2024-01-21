/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:45:54 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/20 18:45:12 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int in_map_bound(t_map *m, int x, int y)
{
    return x >= 0 && y >= 0 && x < m->w && y < m->h;
}

void render_map(t_data *d)
{
    int j = 0;
    int i;
    double x = d->pos[0];
    double y = d->pos[1];
    int dx, dy;
    int color;
    while (j < d->minimap->size)
    {
        i = 0;
        while (i < d->minimap->size)
        {
            dx = (int)(x + d->minimap->zoom * i - (d->minimap->zoom * d->minimap->size) / 2);
            dy = (int)(y + d->minimap->zoom * j - (d->minimap->zoom * d->minimap->size) / 2);
            // printf("%d %d\n", dx, dy);
            if(in_map_bound(d->map, dx, dy) && d->map->v[dy][dx] == '0')
                color = rgbt(190, 190, 190, 255);
            else if(in_map_bound(d->map, dx, dy) && d->map->v[dy][dx] == '1')
                color = rgbt(150, 75, 0, 255);    
            else
                color = rgbt(50, 50, 50, 255);
            mlx_put_pixel(d->image, i + d->minimap->x, j + d->minimap->y, color);
            i++;
        }
        j++;
    }
    draw_rec(d->image, d->minimap->x, d->minimap->y, d->minimap->size, d->minimap->size, rgbt(255, 255, 255, 255));
    draw_line(d->image, (d->minimap->size / 2) + d->minimap->x, (d->minimap->size / 2) + d->minimap->y, (d->minimap->size/2 + d->minimap->x) + d->dir[0] * 20, (d->minimap->size/2 + d->minimap->y) + d->dir[1] * 20, rgbt(255, 40, 40, 255));
}