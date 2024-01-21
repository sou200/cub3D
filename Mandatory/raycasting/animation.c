/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:51:09 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/20 14:49:21 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void weapon_anim(t_data *data)
{
    unsigned int s_y = HIGHT - data->anim->frames[data->anim->i]->height;
    unsigned int s_x = WIDTH - data->anim->frames[data->anim->i]->width;
    int j = s_y;
    unsigned char *color_addr;
    static int frame;
    while(j < HIGHT)
    {
        int i = s_x;
        while(i < WIDTH)
        {
            color_addr = data->anim->frames[data->anim->i]->pixels + ((j - s_y) * data->anim->frames[data->anim->i]->width + (i - s_x)) * 4;
            if(color_addr[0] != 0 || color_addr[1] != 255 || color_addr[2] != 255)
                mlx_put_pixel(data->image, i, j, rgbt(color_addr[0], color_addr[1], color_addr[2], color_addr[3]));
            i++;
        }
        j++;
    }
    if(data->anim->anim_state)
    {
        if(!(frame%3))
            data->anim->i++;
        else if(data->anim->i == 45)
        {
            data->anim->i = 0;
            data->anim->anim_state = 0;
            frame = 0;
        }
        frame++;
    }
}