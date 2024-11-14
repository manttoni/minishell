#include "minishell.h"


static void expand_heredoc(char *line, int fd, t_env *env)
{
    char    *expanded;

    if (!line || fd < 0)
        return;
    expanded = expand(line, env);
    if (expanded)
    {
        ft_putendl_fd(expanded, fd);
        free(expanded);
    }
}

void unexpected_eof(char *i, char *eof)
{
    if (!i)
        i = "0";
    ft_putstr_fd("-minishell: warning: here-document at line ", 2);
	ft_putstr_fd(i, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
}

int process_heredoc_input(char *eof, t_env *env)
{
    int fd;
    char *s;
    int i;

    setup_heredoc_signals();
    fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC |O_APPEND, 0644);
    if (fd == -1)
        exit(printf(".here_doc not found"));
    i = 0;
    while (42)
    {
        s = readline("> ");
        if (g_signal == 2)
			return -2;
            //exit(130);
        if (!s )
        {
            unexpected_eof(ft_itoa(i), eof);
            break;
        }
            
        if (!ft_strcmp(s, eof))
        {
            free(s);
            break;
        }
        expand_heredoc(s, fd, env);
    }
    close(fd);
    exit(0); 
}


int handle_heredoc_redirection(t_token *token, t_env *env)
{
    pid_t pid;
    char *eof;
    int status;
    int code;
	signal(SIGINT, SIG_IGN);

    eof = token->next->string;
    pid = fork();
    if (pid < 0)
        exit(printf("fork has failed"));
    else if (!pid)
        if (process_heredoc_input(eof, env) == -2)
			return -2;
    waitpid(pid, &status, 0);
     if (WIFEXITED(status))
        code = WEXITSTATUS(status);
    if (code)
    {
        env->exit_code = code;
        g_signal = 0;
        return (-1);
    } 
    else
        return (open(".here_doc", O_RDONLY));
}
