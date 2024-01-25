#include "cub3d.h"
#include <string.h>

void render_game(t_data *d)
{
    t_ray ray;

    for(int i = 0; i < WIDTH; i++)
    {
        t_dbl cam = (2.0 * i)/WIDTH - 1;
        set_vector(ray.dir, d->dir[0] + d->plan[0] * cam, d->dir[1] + d->plan[1] * cam);
        ray.dx = (ray.dir[0] == 0)? MAXFLOAT : fabs(1/ray.dir[0]);
        ray.dy = (ray.dir[1] == 0)? MAXFLOAT : fabs(1/ray.dir[1]);
        raycaster(d, &ray);
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
            my_mlx_put_pixel(d->image, i, j, rgbt(o * pixel[0], o * pixel[1], o * pixel[2], pixel[3]));
            textY += step;
            j++;
        }

        // textures end.
    
        // draw_line(d->image, i, beg, i, end);
    }
}

void game_loop(void *g)
{
    t_data *data;
    data = (t_data *)g;
    mlx_delete_image(data->mlx, data->image);
    data->image = mlx_new_image(data->mlx, WIDTH, WIDTH);
    render_floor_celling(data);
    render_game(data);
    weapon_anim(data);
    if(data->anim->anim_state && data->anim->i >= 45)
    {
        data->anim->i = 0;
        data->anim->anim_state = 0;
    }
    render_map(data);
    mlx_image_to_window(data->mlx, data->image, 0, 0);
}

void f()
{
    system("leaks cub3d");
}

int main(int ac, char **av)
{
    // atexit(f);
    t_data *d;

    printf("Ana Zaml\n");
    d = game_init(ac, av);
    mlx_loop_hook(d->mlx, game_loop, d);
    mlx_loop_hook(d->mlx, key_hook, d);
    mlx_loop_hook(d->mlx, mouse_loop, d);
    mlx_close_hook(d->mlx, close_hook, d);
    mlx_mouse_hook(d->mlx, mouse_key_hook, d);
    mlx_set_cursor_mode(d->mlx, MLX_MOUSE_DISABLED);
    mlx_loop(d->mlx);
    terminate(d, EXIT_SUCCESS, NULL, 0);
}