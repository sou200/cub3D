/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:53:34 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/28 19:55:59 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	just_line(char *line)
{
	int		i;
	int		one;

	one = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		if (line[i] == '1')
			one++;
		i++;
	}
	if (one < 1)
		return (0);
	return (1);
}

char	**make_mwipa(char **map, int i)
{
	char		**mwipa;
	int			j;

	j = i;
	while (map[j])
		j++;
	mwipa = malloc(sizeof(char *) * (j - i + 1));
	if (!mwipa)
		exit(1);
	j = 0;
	while (map[i + j])
	{
		mwipa[j] = map[i + j];
		j++;
	}
	mwipa[j] = NULL;
	return (mwipa);
}

int	wnse(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	valid_player(char **mwipa, int i, int c)
{
	char		*dire;
	int			d;

	if ((length(mwipa[i + 1]) - 1) < c || (length(mwipa[i - 1]) - 1) < c)
		return (1);
	dire = malloc(5);
	if (!dire)
		return (exit(1), 1);
	dire[4] = '\0';
	d = 0;
	dire[0] = mwipa[i - 1][c];
	dire[1] = mwipa[i + 1][c];
	dire[2] = mwipa[i][c - 1];
	dire[3] = mwipa[i][c + 1];
	while (dire[d])
	{
		if (dire[d] != '0' && dire[d] != '1' && !wnse(dire[d]))
			return (free(dire), 1);
		d++;
	}
	return (free(dire), 0);
}

int	end_line(char *line)
{
	int		i;

	i = length(line) - 2;
	while (line[i] == ' ')
		i--;
	if (line[i] == '1')
		return (0);
	return (1);
}
