/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:57 by amaula            #+#    #+#             */
/*   Updated: 2024/10/02 17:17:40 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, char **env)
{
	char	*path;

	if (args[1] == NULL || ft_strcmp(args[1], "") == 0)
		path = ft_getenv("HOME", env);
	else
		path = args[1];
	if (chdir(path) != 0)
		return (error_return("chdir"));
	return (1);
}

int	ft_export(char **args, char **env)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		env = add(env, args[i]);
		if (env == NULL)
			return (error_return("add"));
		i++;
	}
	return (1);
}

int	ft_unset(char **args, char **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_remove(env, args[i]) == 0)
			return (error_return("remove"));
		i++;
	}
	return (1);
}

int	run_builtin(char **args, char **env)
{
	if (ft_strcmp("cd", args[0]) == 0)
		if (ft_cd(args, env) == 0)
			return (error_return("ft_cd"));
	if (ft_strcmp("export", args[0]) == 0)
		if (ft_export(args, env) == 0)
			return (error_return("ft_export"));
	if (ft_strcmp("unset", args[0]) == 0)
		if (ft_unset(args, env) == 0)
			return (error_return("ft_unset"));
	return (1);
}
