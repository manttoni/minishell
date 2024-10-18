/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:48:11 by amaula            #+#    #+#             */
/*   Updated: 2024/10/18 17:16:27 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_token(t_token *token)
{
	while (token)
	{
		printf("type=%d string=%s\n", token->type, token->string);
		token = token->next;
	}
}

void	free_token_list(t_token *token)
{
	if (token->next)
		free_token_list(token->next);
	free(token);
}

int	get_type(char *line)
{
	if (*line == '\'')
		return (SINGLE);
	if (*line == '\"')
		return (DOUBLE);
	if (*line == '|')
		return (PIPE);
	if (ft_strncmp("<<", line, 2) == 0)
		return (HEREDOC);
	else if (*line == '<')
		return (IN);
	if (ft_strncmp(">>", line, 2) == 0)
		return (APPEND);
	else if (*line == '>')
		return (OUT);
	return (WORD);
}	

char	*get_word(char *line)
{
	char	*ptr;

	ptr = line;
	while (*ptr && ft_strchr("|<>\"\' ", *ptr) == NULL)
		ptr++;
	return (ft_substr(line, 0, ptr - line));
}

char	*get_string(t_token *token, char *line)
{
	if (token->type == SINGLE)
		return (ft_substr(line, 0, (ft_strchr(line + 1, '\'') - line) + 1));
	if (token->type == DOUBLE)
		return (ft_substr(line, 0, ft_strchr(line, '\"') - line + 1));
	if (token->type == PIPE)
		return (ft_strdup("|"));
	if (token->type == HEREDOC)
		return (ft_strdup("<<"));
	if (token->type == IN)
		return (ft_strdup("<"));
	if (token->type == APPEND)
		return (ft_strdup(">>"));
	if (token->type == OUT)
		return (ft_strdup(">"));
	return (get_word(line));
}

/* Creates a token, then sets *line to the end of that token */
t_token	*get_token(char *line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = get_type(line);
	token->string = get_string(token, line);
	token->next = NULL;
	if (!token->string)
	{
		free(token->string);
		free(token->next);
		free(token);
		return (NULL);
	}
	return (token);
}

t_token	*get_last(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

void	add_token(t_token **start, t_token *new)
{
	t_token	*last;

	if (*start == NULL)
		*start = new;
	else
	{
		last = get_last(*start);
		last->next = new;
	}
}

/* Creates a linked list where each node is a token
   A token has attributes:
   	-type
	-string
	-next */
t_token	*create_token_list(char *line)
{
	t_token	*start;
	t_token	*new;
	char	*ptr;

	start = NULL;
	ptr = line; // dont change line pointer in loop
	while (*ptr)
	{
		new = get_token(ptr);
		if (!new)
		{
			free_token_list(start);
			return (NULL);
		}
		add_token(&start, new);
		ptr += ft_strlen(new->string);
		while (*ptr && ft_strchr(" ", *ptr)) // add other space characters
			ptr++;
	}
	return (start);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;

	tokens = create_token_list(argv[1]);
	print_token(tokens);
	free_token_list(tokens);
	return (0);
}
