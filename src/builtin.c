/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:57 by amaula            #+#    #+#             */
/*   Updated: 2024/10/10 13:18:07 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (args[1] == NULL || ft_strcmp(args[1], "") == 0)
		path = ft_getenv("HOME", env);
	else
		path = ft_strdup(args[1]);
	if (chdir(path) != 0)
	{
		free(path);
		return (error_return("chdir"));
	}
	free(path);
	return (1);
}

int	ft_export(char **args, t_env *env)
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
		env->arr = add(env->arr, ft_strdup(args[i]));
		if (env->arr == NULL)
			return (error_return("add"));
		i++;
	}
	return (1);
}

int	ft_unset(char **args, t_env *env)
{
	printf("not done\n");
	return (0);
}

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < len(env->arr))
	{
		printf("%s\n", env->arr[i]);
		i++;
	}
	return (1);
}

int	run_builtin(char **args, t_env *env)
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
	if (ft_strcmp("env", args[0]) == 0)
		if (ft_env(env) == 0)
			return (error_return("ft_env"));
	return (1);
}
