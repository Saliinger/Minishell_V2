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
	res = (char *)malloc(sizeof(char) * (pipe_position + 1));
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
	res = (char *)malloc(sizeof(char) * (ft_strlen(in + pipe_position) + 1));
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
		if (!command->arg)
			return (free_command(command));
		command->subcommand = command_init(remove_first_cmd(in,
					command->pipe_position));
		if (!command->subcommand)
			return (free_command(command));
	}
	else
	{
		command->subcommand = NULL;
		command->arg = split_element(ft_strdup(in), ' ');
		if (!command->arg)
			return (command->arg = NULL, free_command(command));
	}
}

t_command	*trim(char *in, char *in_command, bool builtin, int id)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->in = ft_strdup(in);
	command->pipe_position = check_pipe(in);
	init_command_arg(command, in);
	command->command = ft_strdup(in_command);
	command->builtin = builtin;
	command->id = id;
	command->pid = -1;
	command->pipe_fds[0] = -1;
	command->pipe_fds[1] = -1;
	command->outfile_fd = -1;
	command->infile_fd = -1;
	command->clean_arg = NULL;
	command->redirection = NULL;
	free(in);
	free(in_command);
	return (command);
}
