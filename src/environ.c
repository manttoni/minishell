/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/01 17:50:15 by amaula           ###   ########.fr       */
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

char	*ft_getenv(char	*key)
{
	int		fd;
	char	*line;
	int		len;
	char	*ret;

	len = ft_strlen(key);
	fd = open(".env", O_RDONLY);
	if (fd < 0)
	{
		printf("open .env\n");
		return (NULL); // this is wrong
	}
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strnstr(line, key, len))
		{
			ret = ft_substr(line, len + 1, ft_strlen(line + len) - 1);
			free(line);
			close(fd);
			return (ret);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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

