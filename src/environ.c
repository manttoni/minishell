/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/01 19:17:56 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	expand(char **args, int i)
{
	char	*value;

	value = ft_getenv(args[i] + 1);
	free(args[i]);
	if (value != NULL)
	{
		args[i] = value;
		return ;
	}
	while (args[i])
	{
		args[i] = args[i+1];
		i++;
	}
}
	

int	replace_env_vars(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
			expand(args, i);
		i++;
	}
	return (1);
}

