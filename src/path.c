/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:16:13 by mshabano          #+#    #+#             */
/*   Updated: 2024/10/29 20:18:01 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

char *print_error(char *s, int n)
{
	if (n == 2)
		printf("%s\n", s);
	if (n == 1)
		printf("-minishell: %s: %s", s, strerror(errno));
	else if (n == 0)
		printf("-minishell: %s", s);
	return (0);
}

char	*fetch_cmd_path(char *cmd, char **path)
{
	t_exec_cmd	c;
	int	i;

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

char *find_path(t_command *cmd, t_env *env)
{
	char *path_var;
	char *result;
	char **path;
	if (access(cmd->args[0], F_OK | X_OK) == 0)
		return (cmd->args[0]);
	path_var = ft_getenv("PATH", env);
	if (!path_var)
	{	
		print_error(cmd->args[0], 0);
		return (print_error(": command not found", 2));
	}
	path = ft_split(path_var, ':');
	if (!path)
	{
		free(path_var);
		return (print_error("memory allocation failure", 0));
	}
	result = fetch_cmd_path(cmd->args[0], path);
	if (!result)
	{
		free(path_var);
		free_arr(path);
		free(path);
		print_error(cmd->args[0], 0);
		return(print_error(": command not found", 2));
	}
	free(path_var);
	free_arr(path);
	free(path);
	return (result);
}
