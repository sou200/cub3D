/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:22:10 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/20 08:24:53 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3d1.h"

static int		unleah(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (-1);
}

static int		count_words( char *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == charset || str[i + 1] == '\0') == 1
				&& (str[i] == charset || str[i] == '\0') == 0)
			words++;
		i++;
	}
	return (words);
}

static void		write_word(char *dest,char *from, char charset)
{
	int	i;

	i = 0;
	while ((from[i] == charset || from[i] == '\0') == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int		write_split(char **split, char *str, char charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == charset || str[i] == '\0') == 1)
			i++;
		else
		{
			j = 0;
			while ((str[i + j] == charset || str[i + j] == '\0') == 0)
				j++;
			if ((split[word] = (char*)malloc(sizeof(char) * (j + 1))) == NULL)
				return (unleah(split, word - 1));
			write_word(split[word], str + i, charset);
			i += j;
			word++;
		}
	}
	return (0);
}

char			**ft_split(char *str, char c)
{
	char	**res;
	int		words;

	words = count_words(str, c);
	if ((res = (char**)malloc(sizeof(char*) * (words + 1))) == NULL)
		return (NULL);
	res[words] = 0;
	if (write_split(res, str, c) == -1)
		return (NULL);
	return (res);
}


char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	if (!(new = malloc(sizeof(char) * (size + 1))))
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

int length(char *s)
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

// 

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
