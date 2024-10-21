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
		return (ft_substr(line, 1, ft_strchr(line + 1, '\'') - 1 - line)); // quotes are trimmed here
	if (token->type == DOUBLE)
		return (ft_substr(line, 1, ft_strchr(line + 1, '\"') - 1 - line)); // and here
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
		if (new->type == DOUBLE) // change e_type, quotes were trimmed earlier
		{
			if (ft_strchr(new->string, '$'))
				new->type = EXPANDABLE;
			else
				new->type = WORD;
			line += 2;
		}
		else if (new->type == SINGLE)
		{
			new->type = WORD;
			line += 2;
		}
		add_token_last(&start, new);
		line = skip_spaces(line);
	}
	free(ptr);
	return (start);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;

	tokens = tokenize_string(ft_strdup(argv[1]));
	printf("List created:\n");
	print_token(tokens);
	free_token_list(tokens);
	return (0);
}
