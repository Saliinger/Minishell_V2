#include "../../include/exec.h"

int ft_exec_builtins(t_minishell *minishell, t_command *command)
{
    int exit = 0;

    if (command->id == 1)
        exit = ft_echo(command);
    else if (command->id == 2)
        exit = ft_cd(command, minishell);
    else if (command->id == 4)
        exit = ft_pwd(minishell);
    else if (command->id == 5)
        exit = ft_export(command, minishell);
    else if (command->id == 6)
        exit = ft_unset(command, minishell);
    else if (command->id == 7)
        exit = ft_env(minishell);
    else if (command->id == 8)
        ft_exit(minishell, command, true);
    return (exit);
}