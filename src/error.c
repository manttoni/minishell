/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:04:26 by mshabano          #+#    #+#             */
/*   Updated: 2024/11/21 17:04:29 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_error(char *s, int n)
{
	if (n == 2 || n == 3)
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	if (n == 1)
	{
		write(2, "-minishell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else if (n == 0)
	{
		write(2, "-minishell: ", 12);
		write(2, s, ft_strlen(s));
	}
	if (n == 3)
		free(s);
	return (NULL);
}
