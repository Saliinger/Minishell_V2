/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_extern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:45:11 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 20:05:23 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exec_extern(t_minishell *minishell, t_command *command)
{
	char	*cmd_path;
	int		err;

	err = 0;
	cmd_path = NULL;
	if (command->clean_arg)
		cmd_path = get_cmd_path(command->clean_arg[0], minishell, &err);
	if (cmd_path && !err)
	{
		if (access(cmd_path, X_OK) == 0)
		{
			if (set_signals_to_default() == -1)
				return (printerr("%s: %d: err\n", __FILE__, __LINE__));
			err = execve(cmd_path, command->clean_arg, minishell->env);
			if (set_signals_to_ignore() == -1)
				return (printerr("%s: %d: err\n", __FILE__, __LINE__));
		}
		err = 126;
		perror("minishell");
	}
	return (err);
}
