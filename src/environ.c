/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/02 17:20:41 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key, char **env)
{
	char	**assignment;
	int		key_len;
	
	assignment = find(env, key);
	key_len = ft_strlen(key);
	return (ft_substr(*assignment, key_len + 1, ft_strlen(*assignment + key_len + 1)));
}

void	expand(char **args, int i, char **env)
{
	char	*value;

	value = ft_getenv(args[i] + 1, env);
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
