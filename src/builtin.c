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

/* For each arg, tries to find all matching results from env->arr
 * if it matches the key exactly, it gets removed from env->arr */
int	ft_unset(char **args, t_env *env)
{
	char	*found;
	int		len;

	while (*args)
	{
		len = ft_strlen(*args);
		found = find(env->arr, *args); // can still be not exact, f.e. "hi" in "hive=42"
		while (found)
		{
			if (found[len] == '=') // if this is true, then "hive" in "hive=42"
			{
				ft_remove(env->arr, found);
				break ;
			}
			found = find(&found + 1, *args); // find the next result
		}
		args++;
	}
	return (1);
}

/* Adds or updates the env variables specified by args
 * if it already exists, it first gets removed */
int	ft_export(char **args, t_env *env)
{
	int		i;
	char	*buf[2]; // a 'vehicle' for something that will be unset

	buf[1] = NULL;
	while (*args)
	{
		i = 0;
		while ((*args)[i])
		{
			if (ft_isalpha((*args)[i]) || (*args)[i] == '_' 
					|| ( i > 0 && ft_isdigit((*args)[i]))) // this char is ok
				i++;
			else if ((*args)[i] == '=') // success, arg has valid key and a '='
			{
				buf[0] = *args;
				if (0) ft_unset(buf, env); // remove earlier value if it exists
				env->arr = add(env->arr, ft_strdup(*args));
				if (env->arr == NULL)
					return (0);
				break ;
			}
			else // forbidden character in key
			{
				printf("-bash: export: '%s': not a valid identifier\n", *args);
				break ;
			}
		}
		args++;
	}
	return (1);
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
		if (ft_export(args + 1, env) == 0)
			return (error_return("ft_export"));
	if (ft_strcmp("unset", args[0]) == 0)
		if (ft_unset(args + 1, env) == 0)
			return (error_return("ft_unset"));
	if (ft_strcmp("env", args[0]) == 0)
		if (ft_env(env) == 0)
			return (error_return("ft_env"));
	return (1);
}
