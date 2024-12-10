/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:35:52 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 22:59:41 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this function will free command at the end of use

#include "../../../include/minishell.h"

static void	free_redir(t_redir *head)
{
	t_redir	*next;

	while (head)
	{
		next = head->next;
		free(head->redir);
		free(head);
		head = next;
	}
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->command)
		free(command->command);
	if (command->in)
		free(command->in);
	if (command->arg)
		ft_free_tab(command->arg);
	if (command->clean_arg)
		ft_free_tab(command->clean_arg);
	if (command->redirection)
		free_redir(command->redirection);
	if (command->subcommand)
		free_command(command->subcommand);
	free(command);
}
