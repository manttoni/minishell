/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:32:14 by amaula            #+#    #+#             */
/*   Updated: 2024/11/23 17:30:34 by amaula           ###   ########.fr       */
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

int	ft_env(t_command *cmd, t_env *env)
{
	int	i;

	free_array(cmd->args);
	cmd->args = ft_calloc(1, sizeof(char *));
	if (cmd->args == NULL)
		return (0);
	cmd->args = add(cmd->args, "echo");
	if (cmd->args == NULL)
		return (0);
	cmd->args = add(cmd->args, "");
	if (cmd->args == NULL)
		return (0);
	i = 0;
	while (env->arr[i])
	{
		if (i == len(env->arr) - 1)
			cmd->args[1] = ft_strjoin(cmd->args[1], env->arr[i]);
		else
			cmd->args[1] = join(ft_strjoin(cmd->args[1], env->arr[i]), "\n");
		if (cmd->args[1] == NULL)
			return (0);
		i++;
	}
	return (1);
}
