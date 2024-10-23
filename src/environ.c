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
	result = malloc(1);
	*result = '\0';
	while (*string)
	{
		if (*string == '$' && string[1]) // dollar without anything after shouldnt be expanded
		{
			value = get_value(&string, env);
			if (value == NULL)
			{
				free(ptr);
				return (NULL);
			}
			result = ft_strjoin(result, value); //doesnt free result, better join needed
			free(value);
			if (result == NULL)
			{
				free(ptr);
				return (NULL);
			}
			continue ;
		}
		buffer[0] = *string;
		result = ft_strjoin(result, buffer);
		string++;
	}
	free(ptr);
	return (result);
}
