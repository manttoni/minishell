#include "minishell.h"

/* Checks if str has only allowed chars until terminator or '=' */
int	is_valid_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str != '=' && *str != '\0')
		return (0);
	return (1);
}

/* For each arg, tries to find all matching results from env->arr
 * if it matches the key exactly, it gets removed from env->arr */
int	ft_unset(char **args, t_env *env)
{
	char	*keyword;
	char	*env_var;

	while (*args)
	{
		if (ft_strchr(*args, '=') != NULL || is_valid_key(*args) == 0)
		{
			args++;
			continue ;
		}
		keyword = ft_strjoin(*args, "=");
		if (keyword == NULL)
			return (0);
		env_var = find(env->arr, keyword);
		ft_remove(env->arr, env_var);
		free(env_var);
		free(keyword);
		args++;
	}
	return (1);
}

/* Adds or updates the env variables specified by args
 * if it already exists, it first gets removed */
int	ft_export(char **args, t_env *env)
{
	char	**key_value;
	char	*buf[2];

	buf[1] = NULL;
	while (*args)
	{
		key_value = ft_split(*args, '=');
		if (key_value == NULL)
			return (0);
		if (is_valid_key(key_value[0]) == 0 || ft_countchar(*args, '=') != 1)
		{
			print_error(ft_strjoin(*args, ": invalid export"), 3);
			free_array(key_value);
			args++;
			continue ;
		}
		buf[0] = key_value[0];
		ft_unset(buf, env);
		env->arr = add(env->arr, *args);
		if (env->arr == NULL)
			return (0);
		args++;
		free_array(key_value);
	}
	return (1);
}
