#include "minishell.h"

int	update_fd(t_command *cmd, t_token *token, t_env *env)
{
	if (token->type == IN || token->type == HEREDOC)
	{
		if (cmd->fdin > 2)
			close(cmd->fdin);
		if (token->type == IN)
			cmd->fdin = open(token->next->string, O_RDONLY);
		else if (token->type == HEREDOC)
			cmd->fdin = handle_heredoc_redirection(token, env);
		if (cmd->fdin < 0)
			return (0);
		return (1);
	}
	if (cmd->fdout > 2)
		close(cmd->fdout);
	if (token->type == OUT)
		cmd->fdout = open(token->next->string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->fdout = open(token->next->string, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fdout < 0)
		return (0);
	return (1);
}

t_command	*create_list(t_token *tokens, t_env *env)
{
	t_command	*start;
	t_command	*current;
	int			i;

	if (tokens == NULL)
		return (NULL);
	start = init_node();
	if (start == NULL)
		return (NULL);
	current = start;
	i = 0;
	start->index = i;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			current->args = add(current->args, ft_strdup(tokens->string));
			if (current->args == NULL)
			{
				free_list(start);
				return (NULL);
			}
		}
		else if (tokens->type == PIPE)
		{
			current->next = init_node();
			if (current->next == NULL)
			{
				free_list(start);
				return (NULL);
			}
			current = current->next;
			current->index = ++i;
		}
		else // IN, OUT, APPEND, HEREDOC
		{
			if (update_fd(current, tokens, env) == 0)
			{
				free_list(start);
				printf("getting fd failed\n");
				return (NULL);
			}
			tokens = tokens->next; // jump to file name so next jump jumps to after filename
		}
		tokens = tokens->next;
	}
	return (start);
}
