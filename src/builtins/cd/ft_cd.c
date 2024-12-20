/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:29:59 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 09:20:11 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// check: perm / type of file : dir or else / is a symlink

static char	*start_path(t_command *command, t_minishell *minishell)
{
	char	*path;

	path = NULL;
	if (!command->clean_arg[1])
		path = get_home(&minishell);
	else if (command->clean_arg[1][0] == '/' || command->clean_arg[1][0] == '~')
	{
		if (command->clean_arg[1][0] == '~')
			path = safe_strdup(command->clean_arg[1] + 1, ALLOC_COMMAND);
		else if (ft_strlen(command->clean_arg[1]) == 1)
			path = safe_strdup(command->clean_arg[1] + 1, ALLOC_COMMAND);
		else
			path = get_path(command->clean_arg[1], minishell);
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
		return (printerr(" too many arguments"), minishell->exit_status[0] = 1,
			1);
	if (!command->clean_arg[1])
		path = get_home(&minishell);
	path = start_path(command, minishell);
	if (!*path)
		path = safe_strdup("/", ALLOC_COMMAND);
	error = chdir(path);
	if (error == 0)
	{
		error = change_pwd(minishell, path);
		if (error != 0)
			printerr("cd: Fail to change PWD or OLDPWD\n");
	}
	else
	{
		printerr(" No such file or directory\n");
		return (minishell->exit_status[0] = 1, 1);
	}
	return (0);
}
// check permission or type
// use of access for perm