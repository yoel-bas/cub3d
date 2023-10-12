/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:55 by melayoub          #+#    #+#             */
/*   Updated: 2022/12/14 13:58:55 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdio.h>
# include<stdlib.h>
# include<fcntl.h>
# include<unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *str1, char *str2);
int		found_newline(char *stash);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *src);
char	*get_linee(char *src);
char	*ft_substr(char *s, unsigned int start, size_t	len);
char	*update_it(char *s);

#endif