/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:41:59 by amaula            #+#    #+#             */
/*   Updated: 2024/08/26 13:29:45 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_join(char *dst, char *src, size_t len)
{
	char			*ret;
	char			*ptr;
	size_t			bytes;
	unsigned int	i;

	if (!*src)
		return (dst);
	if (dst == NULL || src == NULL)
		return (NULL);
	bytes = gnl_strlen(dst) + len + 1;
	ret = malloc(bytes);
	if (ret == NULL)
	{
		free(dst);
		return (NULL);
	}
	i = 0;
	ptr = dst;
	while (*dst)
		ret[i++] = *dst++;
	while (i < bytes - 1)
		ret[i++] = *src++;
	free(ptr);
	ret[i] = '\0';
	return (ret);
}

void	gnl_copy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*gnl_strchr(char *str, char chr)
{
	while (*str)
	{
		if (*str == chr)
			return (str);
		str++;
	}
	return (NULL);
}

void	gnl_bzero(char *buffer, size_t size)
{
	while (size-- > 0)
		buffer[size] = '\0';
}

size_t	gnl_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (*s++)
		len++;
	return (len);
}
