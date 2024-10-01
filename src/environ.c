/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/01 19:17:56 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(char **env)
{
	int		fd;

	fd = open(".env", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (error_return("open .env"));
	while (*env)
	{
		write(fd, *env, ft_strlen(*env));
		write(fd, "\n", 1);
		env++;
	}
	close(fd);
	return (1);
}

char	*ft_getenv(char *key)
{
	char	**env;
	int		i;
	int		len;
	char	*value;

	env = read_file(".env");
	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		len = ft_strchr(env[i], '=') - env[i];
		if (ft_strnstr(env[i], key, len))
		{
			value = ft_substr(env[i], len + 1, ft_strlen(env[i] + len) - 1);
			free_split(env);
			return (value);
		}
		i++;
	}
	free_split(env);
	return (NULL);
}

void	expand(char **args, int i)
{
	char	*value;

	value = ft_getenv(args[i] + 1);
	free(args[i]);
	if (value != NULL)
	{
		args[i] = value;
		return ;
	}
	while (args[i])
	{
		args[i] = args[i+1];
		i++;
	}
}
	

int	replace_env_vars(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
			expand(args, i);
		i++;
	}
	return (1);
}

