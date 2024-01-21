/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:38:04 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/19 02:40:01 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_rec(mlx_image_t *image, int x, int y, int w, int h, int color)
{
    int i = x;
    int j = y;
    while (i <= w + x)
    {
        mlx_put_pixel(image, i, y, color);
        mlx_put_pixel(image, i, y + h, color);
        i++;
    }
    while (j <= h + y)
    {
        mlx_put_pixel(image, x, j, color);
        mlx_put_pixel(image, x + w, j, color);
        j++;
    }
}

int draw_line(mlx_image_t *img, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;

    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

    deltaX /= pixels;
    deltaY /= pixels;

    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
        if(pixelX < 0)
            pixelX = 0;
        else if(pixelX > img->width)
            pixelX = img->width;
        if(pixelY < 0)
            pixelY = 0;
        else if(pixelY > img->height)
            pixelY = img->height;
        mlx_put_pixel(img, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
    return 1;
}
