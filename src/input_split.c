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

char	**cmd_split(char *cmd)
{
	char	**ar;
	char	*arg;

	ar = malloc(sizeof(char *));
	ar[0] = NULL;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		arg = get_arg(cmd);
		ar = add(ar, arg);
		cmd += ft_strlen(arg);
	}
	return (ar);
}
