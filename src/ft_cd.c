/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:32:01 by amaula            #+#    #+#             */
/*   Updated: 2024/11/20 16:32:04 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns:
 * 	- NULL if PATH is unset and command was just "cd"
 * 	- HOME if PATH is set and command was just "cd"
 * 	- "minishell", f.e. if "cd minishell"*/
static char	*get_cd_path(char *arg, t_env *env)
{
	char	*path;

	if (arg == NULL || *arg == '\0')
		path = ft_getenv("HOME", env);
	else
		path = ft_strdup(arg);
	return (path);
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;
	DIR		*dir;

	path = get_cd_path(args[1], env);
	if (path == NULL)
	{
		print_error("cd: HOME not set", 2);
		return (1);
	}
	dir = opendir(path);
	if (!dir)
	{
		print_error(ft_strjoin(path, ": no such directory"), 3);
		free(path);
		return (1);
	}
	closedir(dir);
	if (chdir(path) != 0)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
