/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/10 13:28:50 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key, t_env *env)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env->arr[i])
	{
		if (ft_strncmp(env->arr[i], key, key_len) == 0 && env->arr[i][key_len] == '=')
			return (ft_strdup(env->arr[i] + key_len + 1));
		i++;
	}
	return (NULL);
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
