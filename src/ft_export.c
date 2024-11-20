/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:35:09 by amaula            #+#    #+#             */
/*   Updated: 2024/11/20 16:35:10 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_arg(char *arg)
{
	char	**key_value;

	if (ft_strchr(arg, '=') == NULL)
		return (1);
	key_value = ft_split(arg, '=');
	if (is_valid_key(key_value[0]) == 0)
	{
		print_error(ft_strjoin(arg, ": invalid export"), 3);
		free_array(key_value);
		return (1);
	}
	free_array(key_value);
	return (0);
}

/* Adds or updates the env variables specified by args
 * if it already exists, it first gets removed */
int	ft_export(char **args, t_env *env)
{
	char	*buf[2];
	int		ret;

	ret = 0;
	buf[1] = NULL;
	while (*args)
	{
		ret = validate_arg(*args);
		if (ret != 0)
		{
			print_error(ft_strjoin(*args, ": invalid export"), 3);
			args++;
			continue ;
		}
		buf[0] = ft_substr(*args, 0, ft_strchr(*args, '=') - *args);
		ft_unset(buf, env);
		env->arr = add(env->arr, *args);
		if (env->arr == NULL)
			return (1);
		args++;
		free(buf[0]);
	}
	return (ret);
}
