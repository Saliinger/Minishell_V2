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

// check: perm / type of file : dir or else / is a symlink

static char *start_path(t_command *command, t_minishell *minishell)
{
	char    *path;

	path = NULL;
	if (!command->clean_arg[1])
		path = get_home(&minishell);
	else if (command->clean_arg[1][0] == '/' || command->clean_arg[1][0] == '~')
	{
		if (command->clean_arg[1][0] == '~')
			path = safe_strdup(command->clean_arg[1] + 1, ALLOC_COMMAND);
		else
			path = safe_strdup(command->clean_arg[1], ALLOC_COMMAND);
	}
	else
		path = get_path(command->clean_arg[1], minishell);
	return (path);
}

int	ft_cd(t_command *command, t_minishell *minishell)
{
	int		error;
	char	*path;

	if (nbr_of_line(command->clean_arg) > 2)
		return (printerr("cd: too many arguments\n"), minishell->exit_status[0] = 1, 1);
	path = start_path(command, minishell);
	error = chdir(path);
	if (error == 0)
	{
		error = change_pwd(minishell, path);
		if (error != 0)
			printerr("cd: Fail to change PWD or OLDPWD\n");
	}
	else
	{
		// check permission or type
		// use of access for perm
		printerr(" No such file or directory\n");
		return (minishell->exit_status[0] = 1, 1);
	}
	return (0);
}
