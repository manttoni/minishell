#include "minishell.h"

char	*get_next_command(char *input)
{
	char	*cmd;
	char	*ptr;
	
	cmd = NULL;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '\"')
		{
			ptr++;
			while (*ptr != '\"')
				ptr++;
		}
		else if (*ptr == '|' || *ptr == '\0')
			break ;
		ptr++;
	}
	if (input != ptr)
		cmd = ft_substr(input, 0, ptr - input);
	if (*ptr == '\0')
		ft_memset(input, 0, ft_strlen(input));
	else
		ft_memmove(ptr + 1, input, ft_strlen(ptr + 1));
	return (cmd);
}

t_command	*create_list(char *input)
{
	char		*cmd;
	t_command	*new;
	t_command	*list;

	list = NULL;
	cmd = get_next_command(input);
	while (cmd)
	{
		new = create_node(cmd);
		if (new == NULL)
		{
			printf("create_node\n");
			return (NULL);
		}
		add_node(&list, new);
		cmd = get_next_command(input);
	}
	return (list);
}

int main(void)
{
	char		*input;
	t_command	*list;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		fflush(stdout);
		if (*input)
		{
			add_history(input);
			list = create_list(input);
			if (list == NULL)
			{
				printf("create_list\n");
				return (1);
			}
			run(list);
			free_list(list);
		}
		free(input);
	}
	return (0);
}
