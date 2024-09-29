#include "minishell.h"

char	*get_next_command(char *input)
{
	char	*cmd;
	char	*ptr;
	
	if (*input == '\0')
		return (NULL);
	ptr = input;
	while (ft_strchr("|\0", *ptr) == NULL)
	{
		ptr++;
	}
	cmd = ft_substr(input, 0, ptr - input);
	if (*ptr == '\0')
	{
		printf("ASDASDASDASD\n");
		ft_memset(input, '\0', ft_strlen(input));
	}
	else
	{
		printf("QWEQWEQWE\n");
		ft_memmove(input, ptr + 1, ft_strlen(ptr + 1));
	}
	return (cmd);
}

t_command	*create_list(char *input)
{
	char		*ptr;
	t_command	*new;
	t_command	*list;

	list = NULL;
	ptr = input;
	while (*input)
	{
		ptr = ft_strchr(input, '|');
		if (ptr)
			new = create_node(ft_substr(input, 0, ptr - input));
		else
			new = create_node(ft_strdup(input));
		add_node(&list, new);
		if (!ptr)
			break;
		input = ptr + 1;
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
