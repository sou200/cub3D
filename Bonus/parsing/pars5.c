/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:56:14 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/29 11:45:08 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *str)
{
	write(2, str, length(str));
}

void	put_struc(t_args *args, char **mwipa, int i, int c)
{
	args->dir = mwipa[i][c];
	mwipa[i][c] = '0';
	args->x = c + 0.5;
	args->y = i + 0.5;
	args->p++;
}

int	check_line(t_args *args, char **mwipa, int i)
{
	int		c;

	c = 0;
	while (mwipa[i][c] == ' ')
		c++;
	if (mwipa[i][c] != '1' || end_line(mwipa[i]))
		return (1);
	while (mwipa[i][c] != '\n')
	{
		if (mwipa[i][c] == '0' || wnse(mwipa[i][c]))
		{
			if (valid_player(mwipa, i, c))
				return (1);
			if (wnse(mwipa[i][c]))
				put_struc(args, mwipa, i, c);
		}
		else if (mwipa[i][c] != '1' && mwipa[i][c] != ' ')
			return (1);
		c++;
	}
	return (0);
}

int	map_with(char **map)
{
	int		i;
	int		t;
	int		l;

	i = 0;
	t = 0;
	while (map[i])
	{
		l = length(map[i]);
		if (l > t)
			t = l;
		i++;
	}
	return (t);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
