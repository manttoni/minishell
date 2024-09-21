#include "minishell.h"

int	run_command(char *input)
{
	int		id;
	char	**s;
	char	*exe;

	s = ft_split(input, ' ');
	if (ft_strncmp(s[0], "cd", 2) == 0)
	{
		if (s[1] == NULL || chdir(s[1]) < 0)
			printf("cd failed\n");
		free(s);
		return (1);
	}
	exe = ft_strjoin("/bin/", s[0]);
	id = fork();
	if (id < 0)
	{
		printf("Fork failed\n");
		return (0);
	}
	if (id == 0)
	{
		execve(exe, s, NULL);
		printf("execve failed\n");
		return (0);
	}
	wait(NULL);
	free(s);
	free(exe);
	return (1);
}


int main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		fflush(stdout);
		if (*input)
		{
			add_history(input);
			run_command(input);
		}
		free(input);
	}
	return (0);
}
