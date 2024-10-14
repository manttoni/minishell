/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:56:52 by amaula            #+#    #+#             */
/*   Updated: 2024/10/02 17:38:56 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len(char **ar)
{
	int len;

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
	i = 0;
	while (ar[i])
	{
		new[i] = ar[i];
		i++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	free(ar);
	return (new);
}

char	**find(char **ar, char *str)
{
	while (*ar)
	{
		if (ft_strncmp(*ar, str, ft_strlen(str)) == 0)
			return (ar);
		ar++;
	}
	return (NULL);
}

int	ft_remove(char **ar, char *str)
{
	char	**remove_pointer;

	remove_pointer = find(ar, str);
	if (remove_pointer == NULL)
		return (0);
	free(*remove_pointer);
	while (*remove_pointer)
	{
		*remove_pointer = *(remove_pointer + 1);
		remove_pointer++;
	}
	return (1);
}
