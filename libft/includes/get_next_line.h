/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:46:42 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/12 16:03:18 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

char		*get_next_line(int fd);
char		*ft_strnjoin_gnl(char const *s1, char const *s2, size_t n);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strchr_gnl(const char *str, int charsearch);
void		ft_bzero_gnl(void *s, size_t nb);
size_t		ft_strlcpy_gnl(char *dest, const char *src, size_t size);
ssize_t		ft_get_index_gnl(char *str, char searched_char);
void		*ft_calloc_gnl(size_t count, size_t size);
char		*readfile_gnl(int fd, char *line, char *rest);

#endif
