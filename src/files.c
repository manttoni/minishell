/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:29:04 by amaula            #+#    #+#             */
/*   Updated: 2024/10/01 18:43:02 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_count(char	*file)
{
	int		len;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_return("open"));
	line = get_next_line(fd);
	len = 0;
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

char	**read_file(char *file)
{
	int		lines;
	char	**file_array;
	char	*line;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open file");
		return (NULL);
	}
	lines = line_count(file);
	file_array = malloc((lines + 1) * sizeof(char *));
	memset(file_array, 0, (lines + 1) * sizeof(char *));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		file_array[i] = line;
		i++;
		line = get_next_line(fd);
	}
	return (file_array);
}
