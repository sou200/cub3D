/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:43:07 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/21 18:24:04 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void free_anim(t_anim *anim)
{
    int i;

    i = 0;
    if(!anim)
        return;
    while(i < anim->n)
    {
        if(anim->frames[i])
            mlx_delete_texture(anim->frames[i]);
        i++;
    }
    free(anim);
}

void free_texts(t_textures *texs)
{
    if(!texs)
        return;
    if(texs->no_tex)
        mlx_delete_texture(texs->no_tex);
    if(texs->so_tex)
        mlx_delete_texture(texs->so_tex);
    if(texs->we_tex)
        mlx_delete_texture(texs->we_tex);
    if(texs->ea_tex)
        mlx_delete_texture(texs->ea_tex);
}

void free_map(t_map *map)
{
    int i;
    i = 0;
    
    if(!map)
        return;
    free_2d(map->v);
    free(map);
}

void free_args(t_args *args, int free_map_f)
{
    if(free_map_f)
        free_2d(args->map);
    free(args->no);
    free(args->so);
    free(args->we);
    free(args->ea);
    free(args);
}

void free_data(t_data *data)
{
    free_texts(data->texs);
    free_anim(data->anim);
    free_map(data->map);
    free(data->minimap);
    free(data);
}

void terminate(t_data *data,int exit_status, t_args *args, int free_args_f)
{
    if(free_args_f)
        free_args(args, 0);
    if(!data)
        return ;
    mlx_terminate(data->mlx);
    free_data(data);
    exit(exit_status);
}