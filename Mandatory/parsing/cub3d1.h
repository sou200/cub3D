#ifndef CUB3D1_H
# define CUB3D1_H

typedef struct s_args 
{
char *no;
char *so;
char *we;
char *ea;
int f_colors[3];
int c_colors[3];
int h;
int w;
double x;
double y;
char dir;
int p;
char **map;
}t_args;

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int	is_a_new_l(char *str, char c);
char	*collector(char *start, char *c_r);
char	*co_helper(char *ret, char *start, char *c_r);
int	length(char *s);
char	*new_beginning(char *str);
char	*line_cuter(char *str);
char	*ft_strdup(char *src);
char	**ft_split(char *str, char c);
t_args*	parsing(int ac, char **av);
void	free_2d(char **map);

#endif