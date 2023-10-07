/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:51:25 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/01 17:49:28 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

// # include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_elem
{
	char	**file;
	char 	**map;
	// char	*path;
}				t_elem;

typedef struct compas
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
}			t_cmp;

typedef struct colors
{
	char	*fl;
	char	*cl;
}			t_clr;

typedef struct s_cube
{
	t_cmp	*cp;
	t_clr	*cl;
	t_elem	*lmt;
}			t_cube;

int		found_newline(char *stash);
char	*update_it(char *s);
char	*get_next_line(int fd);
char	*get_linee(char *src);

void	ft_error(char *str);
size_t	 ft_strlen(char *str);
char	*ft_strdup(char *src);
char	*ft_substr(char	*s, size_t	start, size_t len);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char 	*ft_strcpy(char *src);
int		ft_atoi(const char *str);

void	player_pos_dir(char **file);
void	check_extension(char *path);
void	check_top_bottom(char **map);
void	check_sides(char **map);
void	check_extranous_spaces(char **map);
int	foreign_material(char **map);
void	player_pos_dir(char **map);
void	check_components(char **map);
int 	fullfilled(t_cube *cnt);
int		line_count(char  **dbl, int *j);
int		is_white_space(char x);
void	clr_parse(char *str);

void	read_components(t_cube *content);
void	maper(t_cube	*content, char	*av);


#endif