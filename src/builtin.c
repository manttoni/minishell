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
		return (0);
	}
	free(path);
	return (1);
}

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
			return (0);
		env_var = find(env->arr, keyword);
		ft_remove(env->arr, env_var);
		free(keyword);
		args++;
	}
	return (1);
}

/* Adds or updates the env variables specified by args
 * if it already exists, it first gets removed */
int	ft_export(char **args, t_env *env)
{
	char	**key_value;
	char	*buf[2];

	buf[1] = NULL;
	while (*args)
	{
		if (ft_strchr(*args, '=') == NULL)
		{
			args++;
			continue ;
		}
		key_value = ft_split(*args, '=');
		if (key_value == NULL)
			return (0);
		if (is_valid_key(key_value[0]) == 0)
		{
			free_array(key_value);
			return (0);
		}
		buf[0] = key_value[0];
		ft_unset(buf, env);
		env->arr = add(env->arr, ft_strdup(*args));
		if (env->arr == NULL)
			return (0);
		args++;
		free_array(key_value);
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
	{
		if (ft_cd(args, env) == 0)
			return (0);
	}
	else if (ft_strcmp("export", args[0]) == 0)
	{
		if (ft_export(args + 1, env) == 0)
			return (0);
	}
	else if (ft_strcmp("unset", args[0]) == 0)
	{
		if (ft_unset(args + 1, env) == 0)
			return (0);
	}
	else if (ft_strcmp("env", args[0]) == 0)
	{
		if (ft_env(env) == 0)
			return (0);
	}
	return (1);
}
