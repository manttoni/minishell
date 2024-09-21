/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:21:53 by amaula            #+#    #+#             */
/*   Updated: 2024/05/03 15:31:23 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*uc;

	uc = (unsigned char *) s;
	while (n-- > 0)
	{
		if (*uc == (unsigned char) c)
			return ((void *) uc);
		uc++;
	}
	return (NULL);
}
