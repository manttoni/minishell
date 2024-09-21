/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:37:49 by amaula            #+#    #+#             */
/*   Updated: 2024/04/23 19:22:24 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains(char const *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			len;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1);
	start = 0;
	while (s1[start] && contains(set, s1[start]))
		start++;
	while (s1[len - 1] && contains(set, s1[len - 1]))
		len--;
	if (start >= len)
		return (ft_strdup("\0"));
	len -= start;
	return (ft_substr(s1, start, len));
}
