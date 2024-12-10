#include "../../include/exec.h"

char *find_path(t_minishell *minishell, t_command *command)
{
    int i = 0;

    while (minishell->paths[i])
    {
        if (ft_strcmp(command->clean_arg[0], minishell->paths[i]))
            return (minishell->paths[i]);
    }
    return (NULL);
}

int    ft_exec_extern(t_minishell *minishell, t_command *command)
{
    char *path;

    path = find_path(minishell, command);
    if (!path)
    {
        perror("Paths doesn't exist\n");
        return (1);
    }
    if (execve(path, command->clean_arg, minishell->env) == -1)
    {
        perror("Execution failed\n");
        return (1);
    }
    return (0);
}