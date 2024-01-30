/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 09:19:22 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/29 09:59:30 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_name(int ac, char **av, t_args *args)
{
	if (ac != 2)
		return (free_struct(args), ft_error("Error\n"), ft_error("in args\n"),
			exit(1));
	if (length(av[1]) > 4)
		valid_name(av[1], args);
	else
		return (free_struct(args), ft_error("Error\n"), ft_error("in name\n"),
			exit(1));
}

int	map_lines(char *str)
{
	int		fd;
	int		counter;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\n"), ft_error("in file opening\n"), exit(1), 1);
	line = get_next_line(fd);
	counter = 0;
	while (line)
	{
		free(line);
		counter++;
		line = get_next_line(fd);
	}
	return (free(line), close(fd), counter);
}

char	**map_copy(char *str, t_args *args)
{
	char	**map;
	int		lines;
	int		i;
	int		fd;

	lines = map_lines(str);
	map = malloc((lines + 1) * (sizeof(char *)));
	if (!map)
		(exit(1));
	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (free_struct(args), free(map), ft_error("Error\n"),
			ft_error("in file opening\n"), exit(1), NULL);
	map[i] = get_next_line(fd);
	while (map[i])
	{
		i++;
		map[i] = get_next_line(fd);
	}
	return (close(fd), map);
}

void	put_null(t_args *args)
{
	int	i;

	i = 0;
	args->no = NULL;
	args->so = NULL;
	args->we = NULL;
	args->ea = NULL;
	args->x = 0;
	args->y = 0;
	args->p = 0;
	while (i < 3)
	{
		args->f_colors[i] = -1;
		args->c_colors[i] = -1;
		i++;
	}
	args->map = NULL;
}

int	com_conter(char *line)
{
	int	i;
	int	com;

	i = 0;
	com = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ',')
			com++;
		i++;
	}
	return (com);
}
