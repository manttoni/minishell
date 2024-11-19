#include "minishell.h"

void	remove_next_token(t_token *token)
{
	t_token	*next;

	if (token->next == NULL)
		return ;
	next = token->next->next;
	free(token->next->string);
	free(token->next);
	token->next = next;
}

void	free_token_list(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->next)
		free_token_list(token->next);
	free(token->string);
	free(token);
}

t_token	*list_last(t_token *list)
{
	t_token	*last;

	if (list == NULL)
		return (NULL);
	last = list;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	add_token_last(t_token **start, t_token *new)
{
	t_token	*last;

	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	last = list_last(*start);
	last->next = new;
}
