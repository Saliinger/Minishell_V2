/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@42mulhouse.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 01:59:00 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/11 01:59:00 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exec(t_minishell *minishell, t_command *command)
{
    int exit = 0;

    if (command->builtin)
        exit = ft_exec_builtins(minishell, command);
    else
        exit = ft_exec_extern(minishell, command);
    free_command(command);
    return (exit);
}
