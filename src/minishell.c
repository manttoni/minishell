#include "minishell.h"

int main(void)
{
	char	*input;
	char	cwd[PATH_MAX];

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		fflush(stdout);
		if (*input)
		{
			add_history(input);
			run_pipeline(input);
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			printf("cwd error\n");
			free(input);
			return (1);
		}
		if (ft_strnstr(cwd, "minishell", ft_strlen(cwd)) == NULL)
		{
			printf("Don't go out!\n");
			free(input);
			return (0);
		}
		free(input);
	}
	return (0);
}
