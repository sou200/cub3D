/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:13:12 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/20 14:21:17 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_factor(enum player_state state)
{
    if(state == MOVE_RIGHT || state == MOVE_FORWARD || state == ROT_RIGHT)
        return 1;
    return -1;
}

void player_move(t_data *data, enum player_state state)
{
    t_dbl Px;
    t_dbl Py;
    int factor;

    Px = data->pos[0];
    Py = data->pos[1];
    factor = get_factor(state);
    if(state == MOVE_FORWARD || state == MOVE_BACKWARD)
    {
        if(data->map->v[(int)Py][(int)(Px + factor * M_VOL * data->dir[0])] == '0')
            Px += factor * M_VOL * data->dir[0];
        if(data->map->v[(int)(Py + factor * M_VOL * data->dir[1])][(int)Px] == '0')
            Py += factor * M_VOL * data->dir[1];
    }
    else
    {
        if(data->map->v[(int)Py][(int)(Px + factor * M_VOL * data->plan[0])] == '0')
            Px += factor * M_VOL * data->plan[0];
        if(data->map->v[(int)(Py + factor * M_VOL * data->plan[1])][(int)Px] == '0')
            Py += factor * M_VOL * data->plan[1];
    }
    data->pos[0] = Px;
    data->pos[1] = Py;
}

void player_rotate_key(t_data *data, enum player_state state)
{
    int factor;

    factor = get_factor(state);
    rotate_vector(data->dir, factor * R_VOL * M_PI);
    rotate_vector(data->plan, factor * R_VOL * M_PI);
}

void player_rotate(t_data *data, t_dbl alpha)
{
    rotate_vector(data->dir, alpha);
    rotate_vector(data->plan, alpha);
}