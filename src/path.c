/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:16:13 by mshabano          #+#    #+#             */
/*   Updated: 2024/11/20 23:45:29 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_cmd_path(char *cmd, char **path)
{
	t_exec_cmd	c;
	int			i;

	i = 0;
	while (path[i] != NULL)
	{
		c.path_part = ft_strjoin(path[i], "/");
		if (!c.path_part)
			return (print_error("ft_strjoin():malloc failed", 0));
		c.executable = ft_strjoin(c.path_part, cmd);
		if (!c.executable)
		{
			free(c.path_part);
			return (print_error("ft_strjoin():malloc failed", 0));
		}
		free(c.path_part);
		if (!access(c.executable, F_OK | X_OK))
			return (c.executable);
		free(c.executable);
		i++;
	}
	return (NULL);
}

int	is_rel(t_command *cmd)
{
	return (!(ft_strncmp(cmd->args[0], "./", 2)));
}

int	full_or_relative_path(t_command *cmd, char **result)
{
	if (!access(cmd->args[0], F_OK | X_OK) && is_rel(cmd))
	{
		*result = cmd->args[0];
		return (1);
	}
	else if (!access(cmd->args[0], F_OK | X_OK) && is_rel(cmd))
	{
		print_error(cmd->args[0], 0);
		print_error(": command not found", 2);
		*result = 0;
		return (1);
	}
	else if (!access(cmd->args[0], F_OK | X_OK) && is_rel(cmd))
	{
		*result = cmd->args[0];
		return (1);
	}
	return (0);
}

char	**split_path_var(t_command *cmd, t_env *env)
{
	char	*path_var;
	char	**path;

	path_var = 0;
	path = 0;
	path_var = ft_getenv("PATH", env);
	if (!path_var)
	{
		print_error(cmd->args[0], 0);
		print_error(": command not found", 2);
		return (0);
	}
	path = ft_split(path_var, ':');
	if (!path)
	{
		free(path_var);
		print_error("memory allocation failure", 0);
		return (0);
	}
	free(path_var);
	return (path);
}

char	*find_path(t_command *cmd, t_env *env)
{
	char	*result;
	char	**path;

	result = 0;
	path = 0;
	if (full_or_relative_path(cmd, &result))
		return (result);
	path = split_path_var(cmd, env);
	if (!path)
		return (0);
	result = fetch_cmd_path(cmd->args[0], path);
	if (!result)
	{
		free_array(path);
		print_error(cmd->args[0], 0);
		return (print_error(": command not found", 2));
	}
	free_array(path);
	return (result);
}
