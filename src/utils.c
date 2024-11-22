/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:16 by amaula            #+#    #+#             */
/*   Updated: 2024/11/22 12:27:37 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Like ft_strjoin, but frees the first pointer */
char	*join(char *freeable, char *suffix)
{
	char	*new;
	int		i;

	if (suffix == NULL)
		free(freeable);
	if (suffix == NULL)
		return (NULL);
	new = malloc(ft_strlen(freeable) + ft_strlen(suffix) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (freeable[i])
	{
		new[i] = freeable[i];
		i++;
	}
	while (*suffix)
	{
		new[i] = *suffix;
		i++;
		suffix++;
	}
	new[i] = '\0';
	free(freeable);
	return (new);
}
