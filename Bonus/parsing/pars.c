/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/01/28 09:04:31 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/28 09:04:31 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**final_map(char **mwipa, t_args *args)
{
	char		**map;
	int			i;
	int			j;

	i = 0;
	map = malloc((args->h + 1) * sizeof(char *));
	if (!map)
		return (exit(1), NULL);
	while (mwipa[i])
	{
		j = 0;
		map[i] = malloc(args->w);
		if (!map[i])
			return (exit(1), NULL);
		while (mwipa[i][j] && mwipa[i][j] != '\n')
		{
			map[i][j] = mwipa[i][j];
			j++;
		}
		while (j < args->w - 1)
			map[i][j++] = ' ';
		map[i][j] = '\0';
		i++;
	}
	return (free(mwipa), map[i] = NULL, map);
}

void	end_of_map(t_args *args, char **map, int i)
{
	char		**mwipa;
	int			j;

	if (!map[i])
		return (free_struct(args), ft_error("Error\n"), ft_error("in map\n"),
			exit(1));
	mwipa = make_mwipa(map, i);
	j = split_len(mwipa);
	if (!just_line(mwipa[0]) || !just_line(mwipa[j - 1]))
		return (free_struct(args), free_2d(map), ft_error("Error\n"),
			ft_error("in map\n"), exit(1));
	i = 1;
	while (i < j - 1)
	{
		if (check_line(args, mwipa, i))
			return (free_struct(args), free_2d(map), ft_error("Error\n"),
				ft_error("in map\n"), exit(1));
		i++;
	}
	args->h = j;
	args->w = map_with(mwipa);
	args->map = final_map(mwipa, args);
	free_2d(map);
}

void	check_struct(t_args *args)
{
	int		i;

	i = 2;
	while (i >= 0)
	{
		if (args->c_colors[i] == -1 || args->f_colors[i] == -1)
			return (free_2d(args->map), free_struct(args), ft_error("Error\n"),
				ft_error("in colors\n"), exit(1));
		i--;
	}
	if (!args->ea || !args->no || !args->so || !args->we)
		return (free_2d(args->map), free_struct(args), ft_error("Error\n"),
			ft_error("in textures\n"), exit(1));
	if (!args->map || args->p != 1)
		return (free_2d(args->map), free_struct(args), ft_error("Error\n"),
			ft_error("in map\n"), exit(1));
}

void	check_map(t_args *args, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i] && !just_line(map[i]))
	{
		if (map[i][0] != '\n')
		{
			while (map[i][j] == ' ')
				j++;
			if (map[i][j] && map[i][j + 1] == ' ')
				colors_fun(args, map[i], j);
			else if (map[i][j] && map[i][j + 1] && map[i][j + 2] == ' ')
				text_fun(args, map[i], j);
			else
				return (free_struct(args), free_2d(map), ft_error("Error\n"),
					ft_error("in map\n"), exit(1));
		}
		i++;
		j = 0;
	}
	end_of_map(args, map, i);
}

t_args	*parsing(int ac, char **av)
{
	t_args		*args;
	char		**map;

	args = malloc(sizeof(t_args));
	if (!args)
		return (exit(1), NULL);
	put_null(args);
	check_name(ac, av, args);
	map = map_copy(av[1], args);
	check_map(args, map);
	check_struct(args);
	args->w--;
	return (args);
}
