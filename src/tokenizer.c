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
	printf("free_token_list\n");
	if (token == NULL)
		return ;
	if (token->next)
		free_token_list(token->next);
	free(token->string);
	free(token);
}

e_type	get_type(char *line)
{
	printf("get_type\n");
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

char	*get_expandable(char *line)
{
	printf("get_expandable\n");
	char	*ptr;
	char	*expa_end;

	ptr = line;
	expa_end = "|<>\"\'$ ";
	while (*ptr && (ft_strchr(expa_end, *ptr) == NULL
			|| ptr == line)) // first $ doesnt count because its part of the expandable
		ptr++;
	return (ft_substr(line, 0, ptr - line));
}

char	*get_word(char *line)
{
	printf("get_word\n");
	char	*ptr;
	char	*word_end;

	ptr = line;
	word_end = "|<>\"\'$ ";
	while (*ptr && ft_strchr(word_end, *ptr) == NULL)
		ptr++;
	return (ft_substr(line, 0, ptr - line));
}

char	*get_string(t_token *token, char *line)
{
	printf("get_string\n");
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
		return (get_expandable(line));
	return (get_word(line));
}

t_token	*get_token(char *line)
{
	printf("get_token from line: %s\n", line);
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
	printf("list_last\n");
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
	printf("add_token_last\n");
	printf("token->string: %s token->type: %d\n", new->string, new->type);
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

void	handle_quotes_expand(t_token *token, t_env *env)
{
	printf("handle_quotes_expand(token->string: %s token->type = %d, env)\n", token->string, token->type);
	if (token->type == DOUBLE && ft_strchr(token->string, '$') != NULL)
		token->type = EXPANDABLE;
	if (token->type == DOUBLE || token->type == SINGLE)
		token->type = WORD;
	if (token->type == EXPANDABLE)
	{
		token->string = expand(token->string, env);
		token->type = WORD;
	}
}

t_token	*tokenize_string(char *line, t_env *env)
{
	printf("tokenize_string(%s, env)\n", line);
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
		if (new->type == SINGLE || new->type == DOUBLE)
			line += 2;
		handle_quotes_expand(new, env);
		if (ft_strlen(new->string) > 0)
			add_token_last(&start, new);
		else
			free_token_list(new);
		line = skip_spaces(line);
	}
	free(ptr);
	return (start);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;
	char	**testarr = ft_split("HOME=/user/home KEY=VALUE", ' ');
	t_env	*envtest = malloc(sizeof(t_env));
	envtest->arr = testarr;

	tokens = tokenize_string(ft_strdup(argv[1]), envtest);
	printf("List created:\n");
	print_token(tokens);
	free_token_list(tokens);
	free_array(envtest->arr);
	free(envtest);
	return (0);
}
