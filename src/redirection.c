#include "minishell.h"

/* returns file name (or delimiter in case of "<<") 
 * or NULL if no redir found ("<", ">", "<<" or ">>") */
char	*extract_filename(char **command, char *redir)
{
	char	*redir_ptr;

	while (*command)
	{
		redir_ptr = ft_strnstr(*command, redir, ft_strlen(*command));
		if (redir_ptr != NULL)
		{
			redir_ptr += ft_strlen(redir);
			if (*redir_ptr != '\0' && ft_strchr("<>", *redir_ptr) == NULL)
				return (ft_strdup(redir_ptr));
			if (*(command + 1) != NULL && ft_strchr("<>", **(command + 1)) == NULL)
				return (ft_strdup(*(command + 1)));
			printf("syntax error\n");
		}
		command++;
	}
	return (NULL);
}

void	ignore_redirs(char **command)
{
	int		redir_found;
	char	*current;
	char	**ptr;

	redir_found = 0;
	ptr = command;
	while (*ptr)
	{
		current = *ptr;
		while (*current)
		{
			if (ft_strchr("<>", *current))
				redir_found = 1;
			if (redir_found)
				*current = '\0';
			current++;
		}
		ptr++;
	}
	while (*command)
	{
		if (**command == '\0')
		{
			free(*command);
			*command = NULL;
		}
		command++;
	}
}
