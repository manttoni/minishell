/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:04:48 by mshabano          #+#    #+#             */
/*   Updated: 2024/10/31 17:04:50 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_heredoc(char *s, int fd, t_env *env)
{
    char *expanded;

    expanded = expand(s, env);
    ft_putendl_fd(expanded, fd);
    free(expanded);
}
void process_heredoc_input(char *eof, t_env *env)
{
    int fd;
    char *s;

    fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC |O_APPEND, 0644);
    if (fd == -1)
        exit(printf(".here_doc not found"));
    while (42)
    {
        s = readline("> ");
        if (!s)
            break;
        if (!ft_strcmp(s, eof))
        {
            free(s);
            break;
        }
        expand_heredoc(s, fd, env);
    }
    close(fd);
     //function to clean shit here
     exit(0);
    
}

int handle_heredoc_redirection(t_token *token, t_env *env)
{
    pid_t pid;
    char *eof;


    //signal function can probaly be here;
    eof = token->next->string;
    pid = fork();
    if (pid < 0)
        exit(printf("fork has failed"));
    else if (!pid)
        process_heredoc_input(eof, env);
    waitpid(0, NULL, 0);
    return (open(".here_doc", O_RDONLY));
}