#include "minishell.h"

int wait_for_children(int num_processes)
{
    int status;
    int last_exit_code = 0;
    int processes_waited = 0;

    while (processes_waited < num_processes)
    {
        if (waitpid(-1, &status, 0) > 0)
        {
            processes_waited++;
            if (processes_waited == num_processes)
            {
                if (WIFEXITED(status))
                    last_exit_code = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                    last_exit_code = 128 + WTERMSIG(status);
            }
        }
    }
    return last_exit_code;
}


