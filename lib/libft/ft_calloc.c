/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:58:06 by amaula            #+#    #+#             */
/*   Updated: 2024/05/10 16:36:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*memory;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	memory = malloc(size * count);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, size * count);
	return ((void *) memory);
}
