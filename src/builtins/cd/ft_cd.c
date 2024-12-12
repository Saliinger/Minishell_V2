/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:29:59 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/11 02:15:55 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(t_command *command, t_minishell *minishell)
{
	int		error;
	char	*path;

	if (nbr_of_line(command->clean_arg) > 2)
		return (printerr("cd: too many arguments\n"), minishell->exit_status[0] = 1, 1);
	path = command->clean_arg[1];
	if (!path)
		return (minishell->exit_status[0] = 1, 1);
	error = chdir(path);
	if (error == 0)
	{
		error = change_pwd(minishell, path);
		if (error != 0)
			printerr("cd: Fail to change PWD and OLDPWD\n");
	}
	else
	{
		printerr(" No such file or directory\n");
		return (minishell->exit_status[0] = 1, 1);
	}
	free(path);
	return (0);
}
