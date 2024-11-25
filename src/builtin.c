/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:32:14 by amaula            #+#    #+#             */
/*   Updated: 2024/11/25 15:29:03 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if str has only allowed chars until terminator or '=' */
int	is_valid_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str != '=' && *str != '\0')
		return (0);
	return (1);
}

/* For each arg, tries to find all matching results from env->arr
 * if it matches the key exactly, it gets removed from env->arr */
int	ft_unset(char **args, t_env *env)
{
	char	*keyword;
	char	*env_var;

	while (*args)
	{
		if (ft_strchr(*args, '=') != NULL || is_valid_key(*args) == 0)
		{
			args++;
			continue ;
		}
		keyword = ft_strjoin(*args, "=");
		if (keyword == NULL)
			return (1);
		env_var = find(env->arr, keyword);
		ft_remove(env->arr, env_var);
		free(env_var);
		free(keyword);
		args++;
	}
	return (0);
}
