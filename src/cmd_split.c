#include "minishell.h"

char	*get_arg(char *cmd)
{
	char	inside;
	char	*ptr;

	inside = 0;
	ptr = cmd;
	while (*ptr)
	{
		if (*ptr == inside) // quote closes
		{
			inside = 0;
			ptr++;
			continue ;
		}
		if (*ptr == '\'' || *ptr == '\"') // quote opens
			inside = *ptr;
		if (*ptr == ' ' && inside == 0)
			return (ft_substr(cmd, 0, ptr - cmd));
		ptr++;
	}
	return (ft_strdup(cmd));
}

char	*replace_dollar(char *arg, char *dollar, char **env)
{
	char	*key;
	char	*value;
	char	*new;
	int		len;
	char	*end_part;

	key = get_key(dollar);
	value = ft_getenv(key, env);
	len = ft_strlen(arg) - ft_strlen(key) - 1;
	len += ft_strlen(value) + 1;
	new = malloc(len * sizeof(char));
	new = ft_substr(arg, 0, dollar - arg);
	new = ft_strjoin(new, value);
	end_part = ft_strdup(arg + (dollar - arg) + 1 + ft_strlen(key));
	new = ft_strjoin(new, end_part);
	free(key);
	free(value);
	free(arg);
	return (new);
}

char	*expand(char *arg, int qstart, int qend, char **env)
{
	char	*dollar;

	dollar = ft_strrchr(arg, '$');
	while (dollar)
	{
		if (dollar - arg >= qstart && dollar - arg < qend)
		{
			arg = replace_dollar(arg, dollar, env);
			//ft_memmove(dollar, dollar + 1, ft_strlen(dollar + 1));
		}
		dollar = ft_strrchr(arg, '$');
	}
	return (arg);
}

char	*format(char *arg, char **env)
{
	char	quote;
	char	*end_quote;
	int		i;

	i = 0;
	quote = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			quote = arg[i];
			ft_memmove(&arg[i], &arg[i + 1], ft_strlen(&arg[i + 1]));
			break ;
		}
		i++;
	}
	if (quote != 0)
	{
		end_quote = ft_strrchr(arg, quote);
		ft_memmove(end_quote, end_quote + 1, ft_strlen(end_quote + 1));
		arg[ft_strlen(arg) - 2] = '\0';
	}
	else
	{
		i = 0;
		end_quote = &arg[ft_strlen(arg)];
	}
	if (quote != '\'')
		arg = expand(arg, i, end_quote - arg, env);
	return (arg);
}

char	**cmd_split(char *cmd, char **env)
{
	char	**ar;
	char	*arg;
	int		len;

	ar = malloc(sizeof(char *));
	ar[0] = NULL;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		if (*cmd == '\0')
			break ;
		arg = get_arg(cmd);
		len = ft_strlen(arg);
		arg = format(arg, env);
		ar = add(ar, arg);
		cmd += len;
	}
	return (ar);
}
