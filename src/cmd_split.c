#include "minishell.h"

char	*append(char *beginning, char *end)
{
	char	*chain;
	int		blen;
	int		elen;
	int		i;

	blen = ft_strlen(beginning);
	elen = ft_strlen(end);
	chain = malloc((blen + elen + 1));
	i = 0;
	while (i < blen)
	{
		chain[i] = beginning[i];
		i++;
	}
	while (i < blen + elen)
	{
		chain[i] = end[i - blen];
		i++;
	}
	chain[i] = '\0';
	free(beginning);
	free(end);
	return (chain);
}

int	get_arg(char **arg, char *cmd, char **env)
{
	char	inside;
	char	*ptr;
	char	*result;
	char	*chrstr;

	inside = 0;
	ptr = cmd;
	result = malloc(1);
	result[0] = '\0';
	while (*ptr)
	{
		if (*ptr == inside) // quote closes
		{
			inside = 0;
			ft_memmove(ptr, ptr + 1, ft_strlen(ptr + 1)); // hide quote
			ptr[ft_strlen(ptr) - 1] = '\0';
		}
		if (*ptr == '\'' || *ptr == '\"') // quote opens
		{
			inside = *ptr;
			ft_memmove(ptr, ptr + 1, ft_strlen(ptr + 1)); // hide quote
			ptr[ft_strlen(ptr) - 1] = '\0';
		}
		if (*ptr == ' ' && inside == 0) // space that is not in quotes
		{
			*arg = result;
			return (ptr - cmd);
		}
		if (*ptr == '$' && inside != '\'') // dollar that is not in single quotes
		{
			result = append(result, ft_getenv(get_key(ptr), env));
			ptr += ft_strlen(get_key(ptr));
		}
		else
		{
			chrstr = malloc(2);
			chrstr[0] = *ptr;
			chrstr[1] = '\0';
			result = append(result, chrstr);
		}
		ptr++;
	}
	*arg = result;
	return (ft_strlen(cmd));
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
		len = get_arg(&arg, cmd, env);
		printf("arg = %s\n", arg);
		ar = add(ar, arg);
		cmd += len;
	}
	return (ar);
}
