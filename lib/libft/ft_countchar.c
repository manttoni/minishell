/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:50:59 by amaula            #+#    #+#             */
/*   Updated: 2024/07/16 11:51:02 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_countchar(char *str, char c)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		if (*str == c)
			counter++;
		str++;
	}
	return (counter);
}
