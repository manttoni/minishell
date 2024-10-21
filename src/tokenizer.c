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
	free(token->string);
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

char	*get_key(char *line)
{
	char	*end;

	if (*line != '$')
		return (NULL);
	if (ft_isalpha(*(line + 1)) == 0 && *(line + 1) != '_')
		return (NULL);
	end = line + 2;
	while (*end)
	{
		if (ft_isalnum(*end) == 0 && *end != '_')
			return (ft_substr(line, 0, end - line));
		end++;
	}
	return (ft_strdup(line)); //or maybe just return line, have to see
}

/* word end is a string of chars that the word CANNOT include. 
 * f.e.	in single quotes it can contain anything except spaces, 
 * 		in double quotes anything except dollar, 
 * 		without quotes many chars will end the word*/
char	*get_word(char *line, char *word_end)
{
	char	*ptr;

	ptr = line;
	while (*ptr && ft_strchr(word_end, *ptr) == NULL)
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
	if (token->type == EXPANDABLE)
		return (get_key(line));
	return (get_word(line, "|<>\"\'$ "));
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

char	*skip_spaces(char *string)
{
	while (*string && ft_strchr(" \f\v\n\t\r", *string))
		string++;
	return (string);
}

t_token	*tokenize_string(char *line)
{
	t_token *start;
	t_token	*new;
	char	*ptr;

	ptr = line;
	start = NULL;
	while (*line)
	{
		new = get_token(line);
		if (!new)
		{
			free_token_list(start);
			free(ptr);
			return (NULL);
		}
		line += ft_strlen(new->string);
		add_token_last(&start, new);
		line = skip_spaces(line);
	}
	free(ptr);
	return (start);
}

t_token	*double_quotes(char *string)
{
	t_token	*sublist; //contains WORD or EXPANDABLE
	t_token	*new;
	char	*ptr;

	ptr = string;
	sublist = NULL;
	while (*ptr)
	{
		new = malloc(sizeof(t_token));
		if (!new)
		{
			free_token_list(sublist);
			return (NULL);
		}
		new->next = NULL;
		if (*ptr == '$')
		{
			new->type = EXPANDABLE;
			new->string = get_key(ptr);
		}
		else
		{
			new->type = WORD;
			new->string = get_word(ptr, "$ ");
		}
		ptr += ft_strlen(new->string);
		add_token_last(&sublist, new);
		ptr = skip_spaces(ptr);
	}
	free(string);
	return (sublist);
}

t_token	*single_quotes(char *string)
{
	t_token	*sublist; // contains only WORD
	t_token	*new;
	char	*ptr;

	ptr = string;
	sublist = NULL;
	while (*ptr)
	{
		new = malloc(sizeof(t_token));
		if (!new)
		{
			free_token_list(sublist);
			return (NULL);
		}
		new->next = NULL;
		new->type = WORD;
		new->string = get_word(ptr, " ");
		ptr += ft_strlen(new->string);
		add_token_last(&sublist, new);
		ptr = skip_spaces(ptr);
	}
	free(string);
	return (sublist);
}

t_token	*handle_quotes(t_token *start)
{
	t_token	*current;
	t_token	*next;
	t_token	*sublist;

	current = start;
	while (current && current->next)
	{
		next = current->next;
		if (next->type == DOUBLE)
			sublist = double_quotes(ft_strtrim(next->string, "\""));
		else if (next->type == SINGLE)
			sublist = single_quotes(ft_strtrim(next->string, "\'"));
		else
		{
			current = next;
			continue ;
		}
		if (!sublist)
			return (NULL);
		current->next = sublist;
		list_last(sublist)->next = next->next;
		current = next->next;
		free(next->string);
		free(next);
	}
	return (start);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;

	tokens = tokenize_string(ft_strdup(argv[1]));
	printf("List created:\n");
	print_token(tokens);
	tokens = handle_quotes(tokens);
	printf("Quotes handled:\n");
	print_token(tokens);
	free_token_list(tokens);
	return (0);
}
