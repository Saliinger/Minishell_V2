/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 01:59:00 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:13:14 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// launch exec for builtins and extern command

int	ft_exec(t_minishell *minishell, t_command *command)
{
	int	exit;

	exit = 0;
	if (command->builtin)
		exit = ft_exec_builtins(minishell, command);
	else
		exit = ft_exec_extern(minishell, command);
	return (exit);
}
