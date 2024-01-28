/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 02:10:28 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/27 20:50:41 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_texts(t_textures *texs)
{
	if (!texs)
		return ;
	if (texs->no_tex)
		mlx_delete_texture(texs->no_tex);
	if (texs->so_tex)
		mlx_delete_texture(texs->so_tex);
	if (texs->we_tex)
		mlx_delete_texture(texs->we_tex);
	if (texs->ea_tex)
		mlx_delete_texture(texs->ea_tex);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	free_2d(map->v);
	free(map);
}

void	free_data(t_data *data)
{
	free_texts(data->texs);
	free_map(data->map);
	free(data);
}
