/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:12:13 by amaula            #+#    #+#             */
/*   Updated: 2024/05/03 18:39:09 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	while (i < len)
	{
		if (s > d)
		{
			d[i] = s[i];
			i++;
		}
		else
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return (dst);
}
