/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:34:59 by eoussama          #+#    #+#             */
/*   Updated: 2024/01/29 10:04:27 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	make_num(char *str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
		{
			return (-1);
		}
		i++;
	}
	num = ft_atoi(str);
	if (num > 255 || num < 0)
		return (-1);
	return (num);
}

void	put_help(t_args *args, char **colors, int i, char c)
{
	int	num;

	num = make_num(colors[i]);
	if (c == 'C')
	{
		if (args->c_colors[i] != -1)
			return (free_struct(args), free_2d(colors), ft_error("Error\n"),
				ft_error("in colors\n"), exit(1));
		args->c_colors[i] = num;
	}
	else if (c == 'F')
	{
		if (args->f_colors[i] != -1)
			return (free_struct(args), free_2d(colors), ft_error("Error\n"),
				ft_error("in colors\n"), exit(1));
		args->f_colors[i] = num;
	}
	else
		return (free_struct(args), free_2d(colors), ft_error("Error\n"),
			ft_error("in colors\n"), exit(1));
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static void	preatoi(int *sign, const char *nptr, int *i)
{
	while ((nptr[*i] >= 9 && nptr[*i] <= 13) || nptr[*i] == ' ')
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *nptr)
{
	long long	result;
	long long	presult;
	int			sign;
	int			i;

	i = 0;
	result = 0;
	sign = 1;
	preatoi(&sign, nptr, &i);
	while (ft_isdigit(nptr[i]))
	{
		presult = result;
		result = result * 10 + nptr[i] - '0';
		if ((result / 10) != presult)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (sign * result);
}
