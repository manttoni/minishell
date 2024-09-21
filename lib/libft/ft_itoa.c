/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:09:06 by amaula            #+#    #+#             */
/*   Updated: 2024/04/22 20:46:44 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	intlen(int n)
{
	if (n >= 10 || n <= -10)
		return (intlen(n / 10) + 1);
	return (1 + (n < 0));
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = intlen(n);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, len + 1);
	if (n < 0)
	{
		*result = '-';
		n = -n;
	}
	while (len-- > 0 && result[len] != '-')
	{
		result[len] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
