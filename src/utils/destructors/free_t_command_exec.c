/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_command_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:37:44 by ekrebs            #+#    #+#             */
/*   Updated: 2024/10/22 20:36:26 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

/**
 * brief : frees the elements of the node
 * uses functions that frees them and sets them to NULL;
 */
static void	free_t_cmd_exec_data_fields(t_command_exec *cmd)
{
	ft_free((void **) &cmd->last_heredoc_str);
	ft_free_nullterm_tab(&cmd->cmd_args);
	ft_free_t_redir(&cmd->redir_files_llist);
}

/**
 * 
 * brief : frees only this t_command_exec node.
 * 
 * 
 */
void	free_t_command_exec_node(t_command_exec **c)
{
	if(!c || !*c)
		return ;
	free_t_cmd_exec_data_fields(*c);
	ft_free((void **) c);
}

/**
 * 
 * brief : frees the struct but not it's data fields (since t_exec_comands is a repackage of t_commands data fields)
 * 
 * 
 */
void	free_t_command_exec(t_command_exec **c)
{
	t_command_exec	*cmd;
	t_command_exec	*tmp;

	if (!c || !*c)
		return ;
	cmd = *c;
	tmp = cmd;
	while (cmd)
	{
		tmp = cmd->next;
		free_t_cmd_exec_data_fields(cmd);
		ft_free((void **) &cmd);
		cmd = tmp;
	}
	*c = NULL;
}