/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:29:59 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:18:44 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_cd(t_command_exec *command, t_minishell *minishell)
{
	int		error;
	char	*path;

	if (nbr_of_line(command->cmd_args) > 2)
		exit(1);
	path = get_path(command->cmd_args[1], minishell);
	if (!path)
		exit(1);
	error = chdir(path);
	if (error == 0)
	{
		error = change_pwd(minishell, path);
		if (error != 0)
			printerr("cd: Fail to change PWD and OLDPWD\n");
	}
	else
	{
		printerr("No such file\n");
		exit(1);
	}
	free(path);
	exit(0);
}
