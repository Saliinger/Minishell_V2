#include "../../include/minishell.h"

int ft_exec(t_minishell *minishell, t_command *command)
{
    int exit = 0;

    if (count_cmd(command) > 1)
        exec_error("minishell: too many arguments", minishell, command);
    else if (command->builtin)
        exit = ft_exec_builtins(minishell, command);
    else
        exit = ft_exec_extern(minishell, command);
    free_command(command);
    return (exit);
}

// if subcommand need to create fork otherwise fuckit

// ft_exec need to check if there's multiple command or pipe + send them to the ft_exec_extern


//    int pid;
//
//    pid = fork();
//    if (pid < 0)
//        exec_error("fork failed\n", minishell, command);
//    if (execve(*minishell->paths, command->clean_arg, minishell->env) == -1)
//    {
//        perror("execve failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // use waitpid to get the exit status of the child
//    waitpid(pid, minishell->exit_status, 0);
//    exec_error(NULL, minishell, command);