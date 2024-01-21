#include "cub3d.h"
#include <string.h>

void close_hook(void *param)
{
    t_data *data;
    data = (t_data *)param;
    terminate(data, EXIT_SUCCESS, NULL, 0);
}

void render_floor_celling(t_data *data)
{
    int j;
    int i;

    (void)data;
    j = 0;
    while (j < HIGHT)
    {
        i = 0;
        if(j < (HIGHT/2))
            while (i < WIDTH)
                mlx_put_pixel(data->image, i++, j, data->c_color);
        else
            while (i < WIDTH)
                mlx_put_pixel(data->image, i++, j, data->f_color);
        j++;
    }
    
}

// void start_anim_weapon(t_data *data)
// {
//     data->anim_state = 1;
// }

t_ray raycaster(t_data *d, t_dbl *rayDir, t_dbl delX, t_dbl delY)
{
        t_ray r;

        ///

        r.dir[0] = rayDir[0];
        r.dir[1] = rayDir[1];

        ///

        int stepX;
        int stepY;

        double ii;
        double jj;

        int mapX = d->pos[0];
        int mapY = d->pos[1];
        double posX = d->pos[0];
        double posY = d->pos[1];

        if(rayDir[0] < 0)
        {
            stepX = -1;
            ii = (posX - mapX) * delX;
        } else {
            stepX = 1;
            ii = (mapX - posX + 1) * delX;
        }
        if(rayDir[1] < 0)
        {
            stepY = -1;
            jj = (posY - mapY) * delY;
        } else {
            stepY = 1;
            jj = (mapY - posY + 1) * delY;
        }
        while(1)
        {
            if(ii < jj)
            {
                r.len = ii;
                ii += delX;
                mapX += stepX;
                r.side = 0;
            } else {
                r.len = jj;
                jj += delY;
                mapY += stepY;
                r.side = 1;
            }
            if(d->map->v[mapY][mapX] == '1')
                break;
        }
        return r;
}

void render_game(t_data *d)
{
    t_ray ray;
    for(int i = 0; i < WIDTH; i++)
    {
        t_dbl cam = (2.0 * i)/WIDTH - 1;
        set_vector(ray.dir, d->dir[0] + d->plan[0] * cam, d->dir[1] + d->plan[1] * cam);
        double delX = (ray.dir[0] == 0)? MAXFLOAT : fabs(1/ray.dir[0]);
        double delY = (ray.dir[1] == 0)? MAXFLOAT : fabs(1/ray.dir[1]);
        ray = raycaster(d, ray.dir, delX, delY);
        int wallHeit = (HIGHT / ray.len);
        int beg = (HIGHT - wallHeit) / 2;
        int end = beg + wallHeit;
        // TODO: textures.

        t_dbl offset;
        if(ray.side)
        {
            offset = d->pos[0] + ray.dir[0] * ray.len;
            if(ray.dir[1] > 0)
                d->t = d->texs->we_tex;
            else
                d->t = d->texs->ea_tex;
        }
        else
        {
            offset = d->pos[1] + ray.dir[1] * ray.len;
            if(ray.dir[0] > 0)
                d->t = d->texs->no_tex;
            else
                d->t = d->texs->so_tex;
        }
        offset -= floor(offset);
        int textX = offset * d->t->width;
        t_dbl textY = 0;
        t_dbl step = (t_dbl)d->t->height / wallHeit;

        if(end > HIGHT)
            end = HIGHT;
        if(beg < 0)
        {
            textY = -(beg * step);
            beg = 0;
        }


        int j = beg;
        while(j < end)
        {
            // t_dbl o = 1.0/(ray.len * 0.5 + 1);
            t_dbl o = 1;
            unsigned char *pixel = d->t->pixels + ((int)textY * d->t->width + (int)textX) * d->t->bytes_per_pixel;
            mlx_put_pixel(d->image, i, j, rgbt(o * pixel[0], o * pixel[1], o * pixel[2], pixel[3]));
            textY += step;
            j++;
        }

        // textures end.
    
        // draw_line(d->image, i, beg, i, end, rgbt(0, 232, 252, 255));
    }
}

void game_loop(void *g)
{
    t_data *data;
    data = (t_data *)g;
    mlx_delete_image(data->mlx, data->image);
    data->image = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
    render_floor_celling(data);
    render_game(data);
    weapon_anim(data);
    if(data->anim->anim_state && data->anim->i >= 45)
    {
        data->anim->i = 0;
        data->anim->anim_state = 0;
    }
    render_map(data);
    int x, y;
    mlx_get_mouse_pos(data->mlx, &x, &y);
    mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void f()
{
    system("leaks cub3d");
}

int main(int ac, char **av)
{
    t_data *d;

    d = game_init(ac, av);
    atexit(f);
    return (1);
    mlx_loop_hook(d->mlx, game_loop, d);
    mlx_loop_hook(d->mlx, key_hook, d);
    mlx_loop_hook(d->mlx, mouse_loop, d);
    mlx_close_hook(d->mlx, close_hook, d);
    mlx_mouse_hook(d->mlx, mouse_key_hook, d);
    mlx_set_cursor_mode(d->mlx, MLX_MOUSE_DISABLED);
    mlx_loop(d->mlx);
    terminate(d, EXIT_SUCCESS, NULL, 0);
}