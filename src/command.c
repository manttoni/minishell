#include "minishell.h"

/* Like GNL, gets commands between pipes,
 * then moves the next command to input.
 * input is still freed in main */
char	**get_next_command(char *input)
{
	char	**command;
	char	*sub;
	int		cmd_len;
	char	*pipe;
	
	if (*input == '\0')
		return (NULL);
	pipe = ft_strchr(input, '|');
	if (pipe == NULL)
	{
		command = ft_split(input, ' ');
		ft_bzero(input, ft_strlen(input));
		return (command);
	}
	cmd_len = pipe - input;
	sub = ft_substr(input, 0, cmd_len);
	command = ft_split(sub, ' ');
	ft_memmove(input, pipe + 1, ft_strlen(input) - cmd_len + 1);
	free(sub);
	return (command);
}
