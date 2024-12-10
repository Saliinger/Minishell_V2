#include "../../include/minishell.h"

int count_cmd(t_command *command)
{
    int i = 0;

    while (command)
    {
        command = command->subcommand;
        i++;
    }
    return (i);
}