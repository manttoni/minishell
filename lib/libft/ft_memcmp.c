/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:24:41 by amaula            #+#    #+#             */
/*   Updated: 2024/05/03 15:23:50 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*c1;
	const unsigned char	*c2;

	if (n == 0)
		return (0);
	c1 = (const unsigned char *)s1;
	c2 = (const unsigned char *)s2;
	while (*c1 == *c2 && n-- > 1)
	{
		c1++;
		c2++;
	}
	return (*c1 - *c2);
}
