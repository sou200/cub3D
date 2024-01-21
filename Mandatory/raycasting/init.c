/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:49:39 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/21 22:40:04 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_player(t_data *d, t_args *args)
{
    set_vector(d->pos, args->x, args->y);
    set_vector(d->dir, 0, 1);
    set_vector(d->plan, -0.66, 0);
    if(args->dir == 'W')
        player_rotate(d, M_PI_2);
    else if(args->dir == 'E')
        player_rotate(d, -M_PI_2);
    else if(args->dir == 'N')
        player_rotate(d, M_PI);
}

void init_animation(t_data *d, t_args *args)
{
    t_anim *a = m_malloc(sizeof(t_anim));
    if(!a)
        terminate(d, EXIT_FAILURE, args, 1);
    a->anim_state = 0;
    a->i = 0;
    a->n = 45;
    char *files[] = {
        "asset/anim/0.png",
        "asset/anim/1.png",
        "asset/anim/2.png",
        "asset/anim/3.png",
        "asset/anim/4.png",
        "asset/anim/5.png",
        "asset/anim/6.png",
        "asset/anim/7.png",
        "asset/anim/8.png",
        "asset/anim/9.png",
        "asset/anim/10.png",
        "asset/anim/11.png",
        "asset/anim/12.png",
        "asset/anim/13.png",
        "asset/anim/14.png",
        "asset/anim/15.png",
        "asset/anim/16.png",
        "asset/anim/17.png",
        "asset/anim/18.png",
        "asset/anim/19.png",
        "asset/anim/20.png",
        "asset/anim/21.png",
        "asset/anim/22.png",
        "asset/anim/23.png",
        "asset/anim/24.png",
        "asset/anim/25.png",
        "asset/anim/26.png",
        "asset/anim/27.png",
        "asset/anim/28.png",
        "asset/anim/29.png",
        "asset/anim/30.png",
        "asset/anim/31.png",
        "asset/anim/32.png",
        "asset/anim/33.png",
        "asset/anim/34.png",
        "asset/anim/35.png",
        "asset/anim/36.png",
        "asset/anim/37.png",
        "asset/anim/38.png",
        "asset/anim/39.png",
        "asset/anim/40.png",
        "asset/anim/41.png",
        "asset/anim/42.png",
        "asset/anim/43.png",
        "asset/anim/44.png",
    };
    for(int i = 0; i < a->n; i++)
    {
        a->frames[i] = mlx_load_png(files[i]);
        if(!a->frames[i])
            terminate(d, EXIT_FAILURE, args, 1);
    }
    d->anim = a;
}

void init_textures(t_data *data, t_args* args)
{
    t_textures *texs;
    texs = m_malloc(sizeof(t_textures));
    if(!texs)
        terminate(data, EXIT_FAILURE, args, 1);
    texs->no_tex = mlx_load_png(args->no);
    texs->so_tex = mlx_load_png(args->so);
    texs->we_tex = mlx_load_png(args->we);
    texs->ea_tex = mlx_load_png(args->ea);
    data->texs = texs;
    if(!texs->no_tex || !texs->so_tex || !texs->we_tex || !texs->ea_tex)
        terminate(data, EXIT_FAILURE, args, 1);
}

void init_minimap(t_data *d, t_args *args)
{
    d->minimap = m_malloc(sizeof(t_minimap));
    if(!d->minimap)
        terminate(d, EXIT_FAILURE, args, 1);
    d->minimap->size = 200;
    d->minimap->x = 20;
    d->minimap->y = 20;
    d->minimap->zoom = 0.05;
}

void init_map(t_data *d, t_args *args)
{
    d->map = m_malloc(sizeof(t_map));
    if(!d->map)
        terminate(d, EXIT_FAILURE, args, 1);
    d->map->v = args->map;
    d->map->w = args->w;
    d->map->h = args->h;
}

t_data* game_init(int ac, char **av)
{
    t_args* args;
    t_data* d;

    args = parsing(ac, av);
    free_args(args, 1); //ff
    return NULL;                   //ff
    d = m_malloc(sizeof(t_data));
    if(!d)
        return terminate(d, EXIT_FAILURE,args, 1), NULL;
    d->f_color = rgbt(args->f_colors[0], args->f_colors[1], args->f_colors[2], 0xff);
    d->c_color = rgbt(args->c_colors[0], args->c_colors[1], args->c_colors[2], 0xff);
    d->mlx = mlx_init(WIDTH, HIGHT, "cub3d", 1);
    d->image = NULL;
    mlx_get_mouse_pos(d->mlx, &d->mouseX, NULL);
    init_player(d, args);
    init_map(d, args);
    init_textures(d, args);
    init_minimap(d, args);
    init_animation(d, args);
    free_args(args, 0);
    // for(int j =0; j < args->h; j++)
    // {
    //     for(int i = 0; i < args->w; i++)
    //     {
    //         printf("%c", d->map->v[j][i]);
    //     }
    //     printf("\n");
    // }
    // printf("%d %d\n", d->map->w, d->map->h);
    return d;
}