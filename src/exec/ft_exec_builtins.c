/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:45:04 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/13 21:45:04 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// execute all builtins

int	ft_exec_builtins(t_minishell *minishell, t_command *command)
{
	int	exit;

	exit = 0;
	if (command->id == ECHO_ID)
		exit = ft_echo(command);
	else if (command->id == CD_ID)
		exit = ft_cd(command, minishell);
	else if (command->id == PWD_ID)
		exit = ft_pwd(minishell);
	else if (command->id == EXPORT_ID)
		exit = ft_export(command, minishell);
	else if (command->id == UNSET_ID)
		exit = ft_unset(command, minishell);
	else if (command->id == ENV_ID)
		exit = ft_env(minishell);
	else if (command->id == EXIT_ID)
		ft_exit(minishell, command, false);
	return (exit);
}
