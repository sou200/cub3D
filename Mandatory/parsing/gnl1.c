/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:42:57 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/28 08:43:14 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	length(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*co_helper(char *ret, char *start, char *c_r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (start[i])
	{
		ret[i] = start[i];
		i++;
	}
	while (c_r[j])
	{
		ret[i++] = c_r[j++];
	}
	ret[i] = '\0';
	return (ret);
}

char	*collector(char *start, char *c_r)
{
	char	*str;

	if (!start)
	{
		start = (char *)malloc(1 * sizeof(char));
		if (!start)
			return (NULL);
		start[0] = '\0';
	}
	if (!c_r)
		return (NULL);
	str = (char *)malloc((length(start) + length(c_r) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = co_helper(str, start, c_r);
	free(start);
	return (str);
}

int	is_a_new_l(char *str, char c)
{
	size_t	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*line_cuter(char *str)
{
	char	*str_r;
	int		i;

	if (!str[0])
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	i += (str[i] == '\n');
	str_r = (char *)malloc((i + 1) * sizeof(char));
	if (!str_r)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		str_r[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		str_r[i++] = '\n';
	str_r[i] = '\0';
	return (str_r);
}
