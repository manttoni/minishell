/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:40:50 by amaula            #+#    #+#             */
/*   Updated: 2024/07/24 15:09:44 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_join(char *dst, char *src, size_t len);
void	gnl_copy(char *dst, char *src);
char	*gnl_strchr(char *str, char chr);
void	gnl_bzero(char *buffer, size_t size);
size_t	gnl_strlen(char *s);

#endif
