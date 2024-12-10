#include "../../include/minishell.h"

void exec_error(char *error, t_minishell *minishell, t_command *command)
{
    if (error)
        perror(error);
    free_minishell(minishell);
    free_command(command);
}