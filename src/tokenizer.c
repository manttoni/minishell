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

char	*skip_spaces(char *string)
{
	while (*string && ft_strchr(" \f\v\n\t\r", *string))
		string++;
	return (string);
}

void	handle_quotes_expand(t_token *token, t_env *env)
{
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
			line += 2; // add quote x 2 to pointer (trimmed earlier)
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
/*
int	main(int argc, char **argv)
{
	t_token	*tokens;
	char	**testarr = ft_split("HOME=/user/home KEY=VALUE", ' ');
	t_env	*envtest = malloc(sizeof(t_env));
	envtest->arr = testarr;

	tokens = tokenize_string(ft_strdup(argv[1]), envtest);
	printf("\n-------------\n");
	printf("List created:\n");
	print_token(tokens);
	free_token_list(tokens);
	free_array(envtest->arr);
	free(envtest);
	return (0);
}*/
