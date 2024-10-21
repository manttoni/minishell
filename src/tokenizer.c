/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:48:11 by amaula            #+#    #+#             */
/*   Updated: 2024/10/18 17:33:04 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_string(char *line, t_token *start);

void	print_token(t_token *token)
{
	if (token == NULL)
		printf("List is empty\n");
	while (token)
	{
		printf("type=%d string=%s\n", token->type, token->string);
		token = token->next;
	}
}

void	free_token_list(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->next)
		free_token_list(token->next);
	free(token);
}

e_type	get_type(char *line)
{
	if (*line == '$')
		return (EXPANDABLE);
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
	if (*ptr == '$') // use get_word for type EXPANDABLE, but skip dollar at i=0
		ptr++;
	while (*ptr && ft_strchr("$|<>\"\' ", *ptr) == NULL)
		ptr++;
	return (ft_substr(line, 0, ptr - line));
}

char	*get_string(t_token *token, char *line)
{
	if (token->type == SINGLE)
		return (ft_substr(line, 0, ft_strchr(line + 1, '\'') - line + 1));
	if (token->type == DOUBLE)
		return (ft_substr(line, 0, ft_strchr(line + 1, '\"') - line + 1));
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

void	add_token_last(t_token **start, t_token *new)
{
	t_token	*last;

	if (*start == NULL)
	{
		printf("List is empty, new token (%s) is now start of list\n", new->string);
		*start = new;
	}
	else
	{
		last = get_last(*start);
		last->next = new;
		printf("Added %s after %s\n", new->string, last->string);
	}
}

/* Checks how to add the token, just at the end, or make a sublist? */
/* Could be used to handle single quotes, but need to figure out how to not expand */
/* Just by trimming double quotes, making a sublist is simple */
int	add_token(t_token **start, t_token *new)
{
	t_token	*sublist;

	printf("Adding: %s of type: %d\n", new->string, new->type);
	if (new->type == DOUBLE)
	{
		sublist = tokenize_string(ft_strtrim(new->string, "\""), *start); // recursive, adds tokens inside quotes to end of list
		if (sublist == NULL) // just checking if it was succesful
		{
			free_token_list(*start);
			return (0);
		}
	}
	else
		add_token_last(start, new);
	return (1);
}


/* Creates a linked list where each node is a token
   A token has attributes:
   	-type
	-string
	-next */
/* Can be given a list which to modify or NULL to create a new one. */
t_token	*tokenize_string(char *line, t_token *start)
{
	t_token	*new;
	printf("Input: %s\n", line);

	while (*line)
	{
		new = get_token(line);
		if (!new)
		{
			free_token_list(start);
			return (NULL);
		}
		if (ft_strlen(new->string) > 0)
		{
			if (add_token(&start, new) == 0)
				return (NULL);
			line += ft_strlen(new->string); // move pointer to the start of next token
		}
		while (*line && ft_strchr(" \f\v\n\t\r", *line)) // skip spaces
			line++;
	}
	return (start);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;

	tokens = tokenize_string(argv[1], NULL);
	print_token(tokens);
	free_token_list(tokens);
	return (0);
}
