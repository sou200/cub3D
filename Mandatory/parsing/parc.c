#include "cub3d1.h"
#include <stdlib.h>
#include <sys/_types/_null.h>

void	ft_error(char *str)
{
	write(2, str, length(str));
}
void	free_2d(char **map)
{
	int i;
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
	int l;
	l = length(str);
	while (l >= 0)
	{
		if (str[l] == '.')
			return (str += l);
		l--;
	}
	return (free_struct(args), ft_error("Error in name\n"), exit(1), NULL);
}

void	valid_name(char *str, t_args *args)
{
	char *dot;
	dot = ft_dot(str, args);
	if (strcmp(dot, ".cub"))
		(free_struct(args), ft_error("Error in name\n"), exit(1));
}

void	check_name(int ac, char **av, t_args *args)
{
	if (ac != 2)
		return (free_struct(args), ft_error("Error in args\n"), exit(1));
	if (length(av[1]) > 4)
		valid_name(av[1], args);
	else
		return (free_struct(args), ft_error("Error in name\n"), exit(1));
}

int	map_lines(char *str)
{
	int fd;
	int counter;
	char *line;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error in file opening\n"), exit(1), 1);
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
	char **map;
	int lines;
	int i;
	int fd;
	lines = map_lines(str);
	map = malloc((lines + 1) * (sizeof(char *)));
	if (!map)
		(exit(1));
	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (free_struct(args), free(map),
			ft_error("Error in file opening\n"), exit(1), NULL);
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
	int i;
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
	int i;
	int com;
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

int	make_num(char *str)
{
	int i;
	int num;
	i = 0;

	while (str[i] && str[i] != '\n')
	{
		if (!isdigit(str[i]))
		{
			return (-1);
		}
		i++;
	}
	num = atoi(str);
	if (num > 255 || num < 0)
		return (-1);
	return (num);
}

void	put_colors(t_args *args, char **colors, char c)
{
	int i;
	int num;
	i = 0;
	while (colors[i])
	{
		num = make_num(colors[i]);
		if (num != -1)
		{
			if (c == 'C')
			{
				if (args->c_colors[i] != -1)
					return (free_struct(args), free_2d(colors),
						ft_error("Error in colors\n"), exit(1));
				args->c_colors[i] = num;
			}
			else if (c == 'F')
			{
				if (args->f_colors[i] != -1)
					return (free_struct(args), free_2d(colors),
						ft_error("Error in colors\n"), exit(1));
				args->f_colors[i] = num;
			}
			else
				return (free_struct(args), free_2d(colors),
					ft_error("Error in colors\n"), exit(1));
		}
		else
			return (free_struct(args), free_2d(colors),
				ft_error("Error in colors\n"), exit(1));
		i++;
	}
}

int	split_len(char **colors)
{
	int i;
	i = 0;
	while (colors[i])
		i++;
	return (i);
}

void	colors_fun(t_args *args, char *line, int j)
{
	char **colors;
	int i;
	int d;
	i = j + 2;
	while (line[i] == ' ')
		i++;
	d = length(line) - 2;
	while (line[d] == ' ')
		d--;
	line[d + 1] = '\0';
	colors = ft_split(line + i, ',');
	if (!colors || com_conter(line) != 2 || split_len(colors) != 3)
		return (free_struct(args), free_2d(colors),
			ft_error("Error in colors\n"), exit(1));
	else
		put_colors(args, colors, line[j]);
}

void	text_fun(t_args *args, char *line, int j)
{
	int i;
	i = j + 2;
	line[length(line) - 1] = '\0';
	while (line[i] == ' ')
		i++;
	if (line[j] == 'N' && line[j + 1] == 'O')
	{
		if (args->no)
			return (free_struct(args), ft_error("Error duplicated\n"),
				exit(1));
		args->no = ft_strdup(line + i);
	}
	else if (line[j] == 'S' && line[j + 1] == 'O')
	{
		if (args->so)
			return (free_struct(args), ft_error("Error duplicated\n"),
				exit(1));
		args->so = ft_strdup(line + i);
	}
	else if (line[j] == 'W' && line[j + 1] == 'E')
	{
		if (args->we)
			return (free_struct(args), ft_error("Error duplicated\n"),
				exit(1));
		args->we = ft_strdup(line + i);
	}
	else if (line[j] == 'E' && line[j + 1] == 'A')
	{
		if (args->ea)
			return (free_struct(args), ft_error("Error duplicated\n"),
				exit(1));
		args->ea = ft_strdup(line + i);
	}
	else
		return (free_struct(args), ft_error("Error in textures\n"), exit(1));
}

int	just_line(char *line)
{
	int i;
	int one;
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
	char **mwipa;
	int j;
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
	char *dire;
	int d;
	if ((length(mwipa[i + 1]) - 1) < c || (length(mwipa[i - 1]) - 1) < c)
		return (1);
	dire = malloc(5);
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
	int i;
	i = length(line) - 2;
	while (line[i] == ' ')
		i--;
	if (line[i] == '1')
		return (0);
	return (1);
}

int	check_line(t_args *args, char **mwipa, int i)
{
	int c;
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
			{
				args->dir = mwipa[i][c];
				mwipa[i][c] = '0'; 
				args->x = c + 0.5;
				args->y = i + 0.5;
				args->p++;
			}
		}
		else if (mwipa[i][c] != '1' && mwipa[i][c] != ' ')
			return (1);
		c++;
	}
	return (0);
}

int	map_with(char **map)
{
	int i;
	int t;
	int l;
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

char	**final_map(char **mwipa, t_args *args)
{
	char **map;
	int i;
	int j;
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
		while (j < args->w -1)
			map[i][j++] = ' ';
		map[i][j] = '\0';
		i++;
	}
	return (free_2d(mwipa),map[i] = NULL,map);
}

void	end_of_map(t_args *args, char **map, int i)
{
	char **mwipa;
	int j;
	if (!map[i])
		return (free_struct(args), ft_error("Error in map\n"), exit(1));
	mwipa = make_mwipa(map, i);
	j = split_len(mwipa);
	if (!just_line(mwipa[0]) || !just_line(mwipa[j - 1]))
		return (free_struct(args), free_2d(map), ft_error("Error in map\n"),
			exit(1));
	i = 1;
	while (i < j - 1)
	{
		if (check_line(args, mwipa, i))
			return (free_struct(args), free_2d(map), ft_error("Error in map\n"),
				exit(1));
		i++;
	}
	// free_2d(map);
	args->h = j;
	args->w = map_with(mwipa);
	args->map = final_map(mwipa, args);
}

void	check_struct(t_args *args)
{
	int i;
	i = 2;
	while (i >= 0)
	{
		if (args->c_colors[i] == -1 || args->f_colors[i] == -1)
			return ( free_2d(args->map),free_struct(args),
				ft_error("Error in colors\n"), exit(1));
		i--;
	}
	if (!args->ea || !args->no || !args->so || !args->we)
		return (free_2d(args->map),free_struct(args),
			ft_error("Error in textures\n"), exit(1));
	if (!args->map || args->p != 1)
		return (free_2d(args->map),free_struct(args), ft_error("Error in map\n"),
			exit(1));
}

void	check_map(t_args *args, char **map)
{
	int i;
	int j;
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
				return (free_struct(args), free_2d(map),
					ft_error("Error in map\n"), exit(1));
		}
		i++;
		j = 0;
	}
	end_of_map(args, map, i);
}

t_args*	parsing(int ac, char **av)
{
	t_args *args;
	char **map;
	args = malloc(sizeof(t_args));
	put_null(args);
	check_name(ac, av, args);
	map = map_copy(av[1], args);
	check_map(args, map);
	check_struct(args);
	args->w--;
	return args;
}