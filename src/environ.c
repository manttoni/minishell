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
	char	*end; // end of substring

	if (ft_isalpha(*(line + 1)) == 0 && *(line + 1) != '_') // key has to start with alpha or _
		return (ft_strdup("$"));
	end = line + 2; // len would be 2 now ($ + first char of key)
	while (*end)
	{
		if (ft_isalnum(*end) == 0 && *end != '_') // rest can also include numericals
			return (ft_substr(line, 1, end - line - 1));
		end++;
	}
	return (ft_strdup(line + 1));
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
			return (&env->arr[i][keylen + 1]); // if not working, use strdup
		}
		i++;
	}
	free(key);
	return ("");
}

/* Expands all env vars in given string */
char	*expand(char *string, t_env *env)
{
	char	*result;
	char	buffer[2];
	char	*value;

	buffer[1] = '\0';
	result = malloc(1);
	*result = '\0';
	while (*string)
	{
		printf("Result: %s\n", result);
		if (*string == '$')
		{
			value = get_value(&string, env);
			printf("value: %s\n", value);
			if (value == NULL)
				return (NULL);
			result = ft_strjoin(result, value); //doesnt free result, better join needed
			if (result == NULL)
				return (NULL);
			continue ;
		}
		buffer[0] = *string;
		result = ft_strjoin(result, buffer);
		string++;
	}
	return (result);
}
