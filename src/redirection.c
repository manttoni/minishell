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
