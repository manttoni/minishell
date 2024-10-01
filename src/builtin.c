/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:57 by amaula            #+#    #+#             */
/*   Updated: 2024/10/01 17:13:42 by amaula           ###   ########.fr       */
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
	(void) args;
	printf("Not ready\n");
	return (0);
}

int	run_builtin(char **args)
{
	if (ft_strcmp("cd", args[0]) == 0)
		if (ft_cd(args) == 0)
			return (error_return("ft_cd"));
	if (ft_strcmp("export", args[0]) == 0)
		if (ft_export(args) == 0)
			return (error_return("ft_export"));
	return (1);
}
