/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:34:58 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/24 05:34:38 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_t	*my_mlx_init(int32_t width, int32_t height, const char *title)
{
	mlx_t	*m;

	if (width <= 0 || height <= 0)
		return (exit(1), NULL);
	m = mlx_init(width, height, title, 0);
	return (m);
}

void	my_mlx_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
		uint32_t color)
{
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	mlx_put_pixel(image, x, y, color);
}
