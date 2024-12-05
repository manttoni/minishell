/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:05:34 by amaula            #+#    #+#             */
/*   Updated: 2024/12/05 17:04:57 by mshabano         ###   ########.fr       */
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

static char	*match_keys(t_env *env, char *key, int keylen)
{
	int	i;

	i = 0;
	while (env->arr[i])
	{
		if (ft_strncmp(env->arr[i], key, keylen) == 0
			&& env->arr[i][keylen] == '=')
		{
			free(key);
			return (ft_strdup(&env->arr[i][keylen + 1]));
		}
		i++;
	}
	return (NULL);
}

/* Takes a pointer that starts with dollar char,
 * returns its value from envs array.
 * Moves dollars value */
char	*get_value(char **dollar, t_env *env)
{
	char	*key;
	int		keylen;
	char	*value;

	key = get_key(*dollar);
	if (key == NULL)
		return (NULL);
	keylen = ft_strlen(key);
	*dollar += keylen + 1;
	if (*key == '?' && keylen == 1)
	{
		free(key);
		return (ft_itoa(env->exit_code));
	}
	value = match_keys(env, key, keylen);
	if (value)
		return (value);
	free(key);
	return (ft_strdup(""));
}

/* Expands all env vars in given string */
char	*expand(char *string, t_env *env)
{
	char	*result;
	char	buffer[2];
	char	*ptr;

	ptr = string;
	buffer[1] = '\0';
	result = ft_calloc(1, 1);
	if (result == NULL)
		return (NULL);
	while (*string)
	{
		if (*string == '$' && string[1])
			process_var_exp(&string, env, &result);
		else
		{
			buffer[0] = *string;
			result = join(result, buffer);
			if (result == NULL)
				break ;
			string++;
		}
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
