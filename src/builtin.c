/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:57 by amaula            #+#    #+#             */
/*   Updated: 2024/10/01 19:38:51 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*path;

	if (args[1] == NULL || ft_strcmp(args[1], "") == 0)
		path = getenv("HOME");
	else
		path = args[1];
	if (chdir(path) != 0)
		return (error_return("chdir"));
	return (1);
}

int	ft_export(char **args)
{
	int	fd;
	int	i;

	i = 1;
	fd = open(".env", O_WRONLY | O_APPEND);
	if (fd < 0)
		return (error_return("open .env"));
	while (args[i])
	{
		if (write(fd, args[i], ft_strlen(args[i])) < 0 || write(fd, "\n", 1) < 0)
		{
			close(fd);
			return (error_return("write"));
		}
		i++;
	}
	close(fd);
	return (1);
}
int	ft_unset(char **args)
{
	char	**env;
	int		fd;

	env = read_file(".env");
	if (env == NULL)
		return (error_return("read_file"));
	close(open(".env", O_WRONLY | O_CREAT | O_TRUNC, 0777));
	fd = open(".env", O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (error_return("open file failed"));
//not ready
	close(fd);
	return (1);
}

int	run_builtin(char **args)
{
	if (ft_strcmp("cd", args[0]) == 0)
		if (ft_cd(args) == 0)
			return (error_return("ft_cd"));
	if (ft_strcmp("export", args[0]) == 0)
		if (ft_export(args) == 0)
			return (error_return("ft_export"));
	if (ft_strcmp("unset", args[0]) == 0)
		if (ft_unset(args) == 0)
			return (error_return("ft_unset"));
	return (1);
}
