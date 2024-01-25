/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:43:28 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 08:03:14 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_frames1(t_anim *a)
{
	a->frames[22] = mlx_load_png("asset/anim/22.png");
	a->frames[23] = mlx_load_png("asset/anim/23.png");
	a->frames[24] = mlx_load_png("asset/anim/24.png");
	a->frames[25] = mlx_load_png("asset/anim/25.png");
	a->frames[26] = mlx_load_png("asset/anim/26.png");
	a->frames[27] = mlx_load_png("asset/anim/27.png");
	a->frames[28] = mlx_load_png("asset/anim/28.png");
	a->frames[29] = mlx_load_png("asset/anim/29.png");
	a->frames[30] = mlx_load_png("asset/anim/30.png");
	a->frames[31] = mlx_load_png("asset/anim/31.png");
	a->frames[32] = mlx_load_png("asset/anim/32.png");
	a->frames[33] = mlx_load_png("asset/anim/33.png");
	a->frames[34] = mlx_load_png("asset/anim/34.png");
	a->frames[35] = mlx_load_png("asset/anim/35.png");
	a->frames[36] = mlx_load_png("asset/anim/36.png");
	a->frames[37] = mlx_load_png("asset/anim/37.png");
	a->frames[38] = mlx_load_png("asset/anim/38.png");
	a->frames[39] = mlx_load_png("asset/anim/39.png");
	a->frames[40] = mlx_load_png("asset/anim/40.png");
	a->frames[41] = mlx_load_png("asset/anim/41.png");
	a->frames[42] = mlx_load_png("asset/anim/42.png");
	a->frames[43] = mlx_load_png("asset/anim/43.png");
	a->frames[44] = mlx_load_png("asset/anim/44.png");
}

void	load_frames(t_anim *a)
{
	a->frames[0] = mlx_load_png("asset/anim/0.png");
	a->frames[1] = mlx_load_png("asset/anim/1.png");
	a->frames[2] = mlx_load_png("asset/anim/2.png");
	a->frames[3] = mlx_load_png("asset/anim/3.png");
	a->frames[4] = mlx_load_png("asset/anim/4.png");
	a->frames[5] = mlx_load_png("asset/anim/5.png");
	a->frames[6] = mlx_load_png("asset/anim/6.png");
	a->frames[7] = mlx_load_png("asset/anim/7.png");
	a->frames[8] = mlx_load_png("asset/anim/8.png");
	a->frames[9] = mlx_load_png("asset/anim/9.png");
	a->frames[10] = mlx_load_png("asset/anim/10.png");
	a->frames[11] = mlx_load_png("asset/anim/11.png");
	a->frames[12] = mlx_load_png("asset/anim/12.png");
	a->frames[13] = mlx_load_png("asset/anim/13.png");
	a->frames[14] = mlx_load_png("asset/anim/14.png");
	a->frames[15] = mlx_load_png("asset/anim/15.png");
	a->frames[16] = mlx_load_png("asset/anim/16.png");
	a->frames[17] = mlx_load_png("asset/anim/17.png");
	a->frames[18] = mlx_load_png("asset/anim/18.png");
	a->frames[19] = mlx_load_png("asset/anim/19.png");
	a->frames[20] = mlx_load_png("asset/anim/20.png");
	a->frames[21] = mlx_load_png("asset/anim/21.png");
	load_frames1(a);
}

void	init_animation(t_data *d, t_args *args)
{
	t_anim	*a;
	int		f_i;

	f_i = -1;
	a = m_malloc(sizeof(t_anim));
	if (!a)
		terminate(d, EXIT_FAILURE, args, 1);
	a->anim_state = 0;
	a->i = 0;
	a->n = 45;
	load_frames(a);
	while (++f_i < a->n)
	{
		printf("%d %p\n", f_i, a->frames[f_i]);
		if (!a->frames[f_i])
			terminate(d, EXIT_FAILURE, args, 1);
	}
	d->anim = a;
}
