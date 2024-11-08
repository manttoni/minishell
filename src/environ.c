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

/* Returns key of env variable without dollar-sign */
char	*get_key(char *line)
{
	char	*expandable;
	char	*key;

	expandable = get_expandable(line);
	if (expandable == NULL)
		return (NULL);
	key = ft_strdup(expandable + 1);
	free(expandable);
	return (key);
}

/* Takes a pointer that starts with dollar char,
 * returns its value from envs array.
 * Moves dollars value */
char	*get_value(char **dollar, t_env *env)
{
	char	*key;
	int		keylen;
	int		i;

	key = get_key(*dollar);
	if (key == NULL)
		return (NULL);
	i = 0;
	keylen = ft_strlen(key);
	*dollar += keylen + 1;
	if (*key == '?' && keylen == 1)
		return (ft_itoa(env->exit_value));
	while (env->arr[i])
	{
		if (ft_strncmp(env->arr[i], key, keylen) == 0
			&& env->arr[i][keylen] == '=') // key matches key of current env element exactly
		{
			free(key);
			return (ft_strdup(&env->arr[i][keylen + 1]));
		}
		i++;
	}
	free(key);
	return (ft_strdup(""));
}

/* Expands all env vars in given string */
char	*expand(char *string, t_env *env)
{
	char	*result;
	char	buffer[2];
	char	*value;
	char	*ptr;

	ptr = string;
	buffer[1] = '\0';
	result = ft_calloc(1, 1);
	while (*string)
	{
		if (*string == '$' && string[1]) // dollar with a following non-null char
		{
			value = get_value(&string, env);
			result = join(result, value);
			if (result == NULL)
			{
				free(value);
				free(ptr);
				free(result);
				return (NULL);
			}
			free(value);
			continue ;
		}
		buffer[0] = *string;
		result = join(result, buffer);
		string++;
	}
	free(ptr);
	return (result);
}

char	*ft_getenv(char *key, t_env *env)
{
	int	i;
	int	keylen;

	i = 0;
	keylen = ft_strlen(key);
	while (env->arr[i])
	{
		if (ft_strncmp(env->arr[i], key, keylen) == 0
				&& env->arr[i][keylen] == '=')
			return (ft_strdup(&env->arr[i][keylen + 1]));
		i++;
	}
	return (NULL);
}
