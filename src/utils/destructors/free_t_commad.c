/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_commad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:45:19 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/10 17:31:18 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

/**
 * brief : frees the elements of the node
 * uses functions that frees them and sets them to NULL;
 */
static void	free_data_fields(t_command *cmd)
{
	ft_free((void **)&cmd->in);
	ft_free((void **)&cmd->command);
	ft_free_nullterm_tab(&cmd->arg);
	ft_free_nullterm_tab(&cmd->clean_arg);
	ft_free_t_redir(&cmd->redirection);
}

/**
 * in : c is &cmds, where cmds is a t_command *cmds
 * brief : for each node, frees the elements of the node of the linked list,
 * then frees the node;
 * sets the cmds to NULL
 *
 */
void	free_t_command(t_command **c)
{
	t_command	*cmds;
	t_command	*tmp;

	if (!c || !*c)
		return ;
	cmds = *c;
	tmp = cmds;
	while (cmds)
	{
		tmp = cmds->subcommand;
		free_data_fields(cmds);
		free(cmds);
		cmds = tmp;
	}
	*c = NULL;
}
