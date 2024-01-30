/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:22:10 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/29 11:26:50 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*new_beginning(char *str)
{
	char	*str_r;
	int		i;
	int		j;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	i += (str[i] == '\n');
	str_r = (char *)malloc(((length(str) + 1) - i) * sizeof(char));
	if (!str_r)
		return (NULL);
	j = 0;
	while (str[i] != '\0' && str)
		str_r[j++] = str[i++];
	str_r[j] = '\0';
	return (free(str), str_r);
}

char	*get_next_line(int fd)
{
	char		*c_r;
	int			reader;
	static char	*start;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	c_r = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!c_r)
		return (NULL);
	reader = 1;
	while (is_a_new_l(start, '\n') == 1 && reader != 0)
	{
		reader = read(fd, c_r, BUFFER_SIZE);
		if (reader == -1)
			return (free(start), start = NULL, free(c_r), NULL);
		c_r[reader] = '\0';
		start = collector(start, c_r);
	}
	free(c_r);
	c_r = line_cuter(start);
	start = new_beginning(start);
	return (c_r);
}
