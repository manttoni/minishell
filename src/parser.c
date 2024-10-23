#include "minishell.h"

char	**get_args(t_token *tokens)
{
	char	**args;

	args = malloc(sizeof(char *));
	*args = NULL;
	while (tokens)
	{
		if (tokens->type != WORD)
		{
			tokens = tokens->next;
			continue ;
		}
		args = add(args, tokens->string);
		tokens = tokens->next;
	}
	return (args);
}


int	parse_cmd(t_command *command, char *cmd, t_env *env)
{
	t_token *tokens = tokenize_string(cmd, env);

	if (tokens == NULL)
		return (error_return("tokenize_string"));
	command->args = get_args(tokens);
	if (command->args == NULL)
		return (error_return("create_args"));
	command->exe = ft_strjoin("/bin/", command->args[0]);
	if (command->exe == NULL)
		return (error_return("strjoin"));
	command->fdin = 0;
	command->fdout = 1;
	return (1);
}
