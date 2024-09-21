#include "minishell.h"

void	free_split(char **s)
{
	char	**ptr;

	ptr = s;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(s);
}

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
		free_split(s);
		return (1);
	}
	exe = ft_strjoin("/bin/", s[0]);
	id = fork();
	if (id < 0)
	{
		printf("Fork failed\n");
		free(exe);
		free_split(s);
		return (0);
	}
	if (id == 0)
	{
		execve(exe, s, NULL);
		printf("execve failed\n");
		free(exe);
		free_split(s);
		return (0);
	}
	wait(NULL);
	free_split(s);
	free(exe);
	return (1);
}


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
			run_command(input);
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