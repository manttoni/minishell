/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:02:14 by mshabano          #+#    #+#             */
/*   Updated: 2024/12/05 17:03:11 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Like ft_strjoin, but frees the first pointer */

int	process_var_exp(char **string, t_env *env, char **result)
{
	char	*value;

	value = 0;
	value = get_value(string, env);
	if (value == NULL)
		return (1);
	*result = join(*result, value);
	free(value);
	if (result == NULL)
		return (1);
	return (0);
}

char	*join(char *freeable, char *suffix)
{
	char	*new;

	if (suffix == NULL)
		free(freeable);
	if (suffix == NULL)
		return (NULL);
	new = malloc(ft_strlen(freeable) + ft_strlen(suffix) + 1);
	if (new == NULL)
	{
		free(freeable);
		return (NULL);
	}
	ft_memcpy(new, freeable, ft_strlen(freeable));
	ft_memcpy(new + ft_strlen(freeable), suffix, ft_strlen(suffix));
	new[ft_strlen(freeable) + ft_strlen(suffix)] = 0;
	free(freeable);
	return (new);
}
