/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 09:13:18 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/29 11:31:47 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_2d(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_struct(t_args *args)
{
	free(args->ea);
	free(args->no);
	free(args->so);
	free(args->we);
	free(args);
}

char	*ft_dot(char *str, t_args *args)
{
	int		l;

	l = length(str);
	while (l >= 0)
	{
		if (str[l] == '.')
			return (str += l);
		l--;
	}
	return (free_struct(args), ft_error("Error\n"), ft_error("in name\n"),
		exit(1), NULL);
}

void	valid_name(char *str, t_args *args)
{
	char	*dot;

	dot = ft_dot(str, args);
	if (ft_strcmp(dot, ".cub"))
		(free_struct(args), ft_error("Error\n"), ft_error("in name\n"),
			exit(1));
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		if (s1[i] < s2[i] || s1[i] > s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}
