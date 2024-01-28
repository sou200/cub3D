/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:34:22 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 04:57:49 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_vector(t_dbl *vec, t_dbl x, t_dbl y)
{
	vec[0] = x;
	vec[1] = y;
}

void	vector_unit(t_dbl *vec)
{
	t_dbl	mag;

	mag = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
	vec[0] /= mag;
	vec[1] /= mag;
}

void	rotate_vector(t_dbl *vec, t_dbl a)
{
	t_dbl	old_x;

	old_x = vec[0];
	vec[0] = vec[0] * cos(a) - vec[1] * sin(a);
	vec[1] = old_x * sin(a) + vec[1] * cos(a);
}
