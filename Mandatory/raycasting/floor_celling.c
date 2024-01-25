/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 04:51:07 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 02:09:25 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_floor_celling(t_data *data)
{
	int	j;
	int	i;

	(void)data;
	j = 0;
	while (j < HIGHT)
	{
		i = 0;
		if (j < (HIGHT / 2))
			while (i < WIDTH)
				my_mlx_put_pixel(data->image, i++, j, data->c_color);
		else
			while (i < WIDTH)
				my_mlx_put_pixel(data->image, i++, j, data->f_color);
		j++;
	}
}
