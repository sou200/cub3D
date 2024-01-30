/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 09:20:47 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/29 11:52:49 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_colors(t_args *args, char **colors, char c)
{
	int	i;
	int	num;

	i = 0;
	while (colors[i])
	{
		num = make_num(colors[i]);
		if (num != -1)
			put_help(args, colors, i, c);
		else
			return (free_struct(args), free_2d(colors), ft_error("Error\n"),
				ft_error("in colors\n"), exit(1));
		i++;
	}
	free_2d(colors);
}

int	split_len(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
		i++;
	return (i);
}

void	colors_fun(t_args *args, char *line, int j)
{
	char	**colors;
	int		i;
	int		d;

	i = j + 2;
	while (line[i] == ' ')
		i++;
	d = length(line) - 2;
	while (line[d] == ' ')
		d--;
	line[d + 1] = '\0';
	colors = ft_split(line + i, ',');
	if (!colors || com_conter(line) != 2 || split_len(colors) != 3)
		return (free_struct(args), free_2d(colors), ft_error("Error\n"),
			ft_error("in colors\n"), exit(1));
	else
		put_colors(args, colors, line[j]);
}

void	text_help(t_args *args, char **arg, char *line, int i)
{
	if (*arg)
		return (free_struct(args), ft_error("Error\n"),
			ft_error("duplicated\n"), exit(1));
	*arg = ft_strdup(line + i);
}

void	text_fun(t_args *args, char *line, int j)
{
	int	i;

	i = j + 2;
	line[length(line) - 1] = '\0';
	while (line[i] == ' ')
		i++;
	if (line[j] == 'N' && line[j + 1] == 'O')
		text_help(args, &args->no, line, i);
	else if (line[j] == 'S' && line[j + 1] == 'O')
		text_help(args, &args->so, line, i);
	else if (line[j] == 'W' && line[j + 1] == 'E')
		text_help(args, &args->we, line, i);
	else if (line[j] == 'E' && line[j + 1] == 'A')
		text_help(args, &args->ea, line, i);
	else
		return (free_struct(args), ft_error("Error\n"),
			ft_error("in textures\n"), exit(1));
}
