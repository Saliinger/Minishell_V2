/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_extern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:45:11 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 00:19:12 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// add a checker if it's something else than a command

// this

char	*build_full_path(char *dir, char *cmd)
{
	char	*full_path;
	int		total_len;

	total_len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = (char *)safe_malloc(sizeof(char) * total_len, ALLOC_COMMAND);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

static char	*get_value(char **splited_path, char *full_path, t_command *command)
{
	int	i;

	i = 0;
	while (splited_path[i])
	{
		full_path = build_full_path(splited_path[i], command->clean_arg[0]);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	*get_path_abs(t_minishell *data, t_command *command)
{
	char	**splited_path;
	char	*full_path;
	char	*tmp;

	full_path = NULL;
	tmp = data->env[get_env_var(data, "PATH", 4)];
	splited_path = ft_split_safe(tmp, ':', ALLOC_COMMAND);
	return (get_value(splited_path, full_path, command));
}

int	ft_exec_extern(t_minishell *minishell, t_command *command)
{
	char	*path;

	path = get_path_abs(minishell, command);
	if (!path)
	{
		perror("Exec: Command not found\n");
		return (127);
	}
	if (execve(path, command->clean_arg, minishell->env) == -1)
	{
		perror("Execution failed\n");
		return (1);
	}
	return (0);
}
