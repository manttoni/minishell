#include "minishell.h"

int	update_fd(t_command *cmd, t_token *token, t_env *env, t_data data)
{
	if (token->type == IN || token->type == HEREDOC)
	{
		if (cmd->fdin > 2)
			close(cmd->fdin);
		if (token->type == IN)
			cmd->fdin = open(token->next->string, O_RDONLY);
		else
			cmd->fdin = handle_heredoc_redirection(token, env, data);
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

t_data create_data(t_command *start, t_token *tokens, t_env *env)
{
	t_data data;

	data.start = start;
	data.tokens = tokens;
	data.env = env;
	return (data);
}

t_command	*create_list(t_token *tokens, t_env *env)
{
	t_command	*start;
	t_command	*current;
	t_token		*current_token;
	int			fd_return;

	if (tokens == NULL)
		return (NULL);
	start = init_node(0);
	if (start == NULL)
		return (NULL);
	current = start;
	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == WORD)
		{
			current->args = add(current->args, current_token->string);
			if (current->args == NULL)
			{
				free_list(start);
				return (NULL);
			}
		}
		else if (current_token->type == PIPE)
		{
			if (current_token->next == NULL)
			{
				print_error("syntax error: pipe last", 2);
				free_list(start);
				return(NULL);
			}
			current->next = init_node(current->index + 1);
			if (current->next == NULL)
			{
				free_list(start);
				return (NULL);
			}
			current = current->next;
		}
		else // IN, OUT, APPEND, HEREDOC
		{
			fd_return = update_fd(current, current_token, env, create_data(start, tokens, env));
			if (fd_return == 0)
			{
				free_list(start);
				return (NULL);
			}
			current_token = current_token->next; // jump to file name so next jump jumps to after filename
		}
		current_token = current_token->next;
	}
	return (start);
}
