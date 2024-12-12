/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:58:12 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:01:15 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*cut_first_cmd(char *in, int pipe_position)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)safe_malloc(sizeof(char) * (pipe_position + 1), ALLOC_COMMAND);
	if (!res)
		return (NULL);
	while (i < pipe_position)
	{
		res[i] = in[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	*remove_first_cmd(char *in, int pipe_position)
{
	char	*res;
	int		i;

	if (in[pipe_position] == '|')
		pipe_position++;
	res = (char *)safe_malloc(sizeof(char) * (ft_strlen(in + pipe_position) + 1), ALLOC_COMMAND);
	if (!res)
		return (NULL);
	i = 0;
	while (in[pipe_position])
	{
		res[i] = in[pipe_position];
		i++;
		pipe_position++;
	}
	res[i] = '\0';
	return (res);
}

static void	init_command_arg(t_command *command, char *in)
{
	if (command->pipe_position > 0)
	{
		command->pipe = true;
		command->arg = split_element(cut_first_cmd(in, command->pipe_position),
				' ');
		command->subcommand = command_init(remove_first_cmd(in,
					command->pipe_position));
		if (!command->subcommand)
			return (free_command(command));
	}
	else
	{
		command->subcommand = NULL;
		command->arg = split_element(safe_strdup(in, ALLOC_COMMAND), ' ');
	}
}

t_command	*trim(char *in, char *in_command, bool builtin, int id)
{
	t_command	*command;

	command = (t_command *)safe_malloc(sizeof(t_command), ALLOC_COMMAND);
	command->in = safe_strdup(in, ALLOC_COMMAND);
	command->pipe_position = check_pipe(in);
	init_command_arg(command, in);
	command->command = safe_strdup(in_command, ALLOC_COMMAND);
	command->builtin = builtin;
	command->id = id;
	command->pid = -1;
	command->pipe_fds[0] = -1;
	command->pipe_fds[1] = -1;
	command->outfile_fd = -1;
	command->infile_fd = -1;
	command->clean_arg = NULL;
	command->redirection = NULL;
	return (command);
}
