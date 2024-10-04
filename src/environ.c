/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/02 17:20:41 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key, char **env)
{
	char	**assignment;
	char	*value;
	int		key_len;
	
	assignment = find(env, key);
	key_len = ft_strlen(key);
	value = ft_strdup(*assignment + key_len + 1);
	return (value);
}

char	*get_key(char *dollar)
{
	char	*key_end;

	key_end = dollar + 1;
	while (ft_strchr(" \"\'\0", *key_end) == NULL)
		key_end++;
	if (key_end == NULL)
		return (ft_strdup(dollar + 1));
	return (ft_substr(dollar + 1, 0, key_end - dollar - 1));
}
