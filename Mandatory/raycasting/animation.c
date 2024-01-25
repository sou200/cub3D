/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:51:09 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 03:51:07 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	next_frame(t_data *data, int *frame)
{
	if (data->anim->anim_state)
	{
		if (!(*frame % 5))
			data->anim->i++;
		else if (data->anim->i == 45)
		{
			data->anim->i = 0;
			data->anim->anim_state = 0;
			*frame = 0;
		}
		(*frame)++;
	}
}

void	weapon_anim(t_data *data)
{
	static int		frame;
	unsigned char	*color_addr;
	int				i;
	int				j;

	data->anim->s_x = WIDTH - data->anim->frames[data->anim->i]->width;
	data->anim->s_y = HIGHT - data->anim->frames[data->anim->i]->height;
	j = data->anim->s_y - 1;
	while (++j < HIGHT)
	{
		i = data->anim->s_x - 1;
		while (++i < WIDTH)
		{
			color_addr = data->anim->frames[data->anim->i]->pixels + ((j
						- data->anim->s_y)
					* data->anim->frames[data->anim->i]->width + (i
						- data->anim->s_x)) * 4;
			if (color_addr[0] != 0 || color_addr[1] != 255
				|| color_addr[2] != 255)
				my_mlx_put_pixel(data->image, i, j, rgbt(color_addr[0],
						color_addr[1], color_addr[2], color_addr[3]));
		}
	}
	next_frame(data, &frame);
}
