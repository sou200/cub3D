/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 01:02:24 by W2Wizard          #+#    #+#             */
/*   Updated: 2024/01/21 11:36:16 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(texture);

	mlx_image_t* image = mlx_new_image(mlx, texture->width, texture->height);
	if (image == NULL)
		return (NULL);

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t i = 0; i < texture->height; i++)
	{
		pixelx = &texture->pixels[(i * texture->width) * texture->bytes_per_pixel];
		pixeli = &image->pixels[(i * image->width) * texture->bytes_per_pixel];
		memmove(pixeli, pixelx, texture->width * texture->bytes_per_pixel);
	}
	return (image);
}

void mlx_delete_texture(mlx_texture_t* texture)
{
	MLX_NONNULL(texture);
	mlx_freen(2, texture->pixels, texture);
}
