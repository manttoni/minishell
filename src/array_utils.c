/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:56:52 by amaula            #+#    #+#             */
/*   Updated: 2024/12/03 22:04:27 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len(char **ar)
{
	int	len;

	len = 0;
	while (ar[len])
		len++;
	return (len);
}

char	**add(char **ar, char *str)
{
	char	**new;
	int		i;

	new = malloc((len(ar) + 2) * sizeof(char *));
	if (new == NULL)
	{
		free(ar);
		return (NULL);
	}
	i = 0;
	while (ar[i])
	{
		new[i] = ar[i];
		i++;
	}
	new[i] = ft_strdup(str);
	if (new[i] == NULL)
	{
		free(new);
		free(ar);
		return (NULL);
	}
	new[i + 1] = NULL;
	free(ar);
	return (new);
}

/* Returns the string where 'str' is found */
char	*find(char **ar, char *str)
{
	while (*ar)
	{
		if (ft_strncmp(*ar, str, ft_strlen(str)) == 0)
			return (*ar);
		ar++;
	}
	return (NULL);
}

void	ft_remove(char **ar, char *str)
{
	if (str == NULL)
		return ;
	while (*ar)
	{
		if (ft_strcmp(*ar, str) == 0)
			break ;
		ar++;
	}
	while (*ar)
	{
		*ar = *(ar + 1);
		ar++;
	}
}
