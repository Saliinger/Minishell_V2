/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:45:22 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 20:48:20 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_cmd(t_command *command)
{
	int	i;

	i = 0;
	while (command)
	{
		command = command->subcommand;
		i++;
	}
	return (i);
}

t_pids_list	*pids_list_safe_addback(int pid, t_pids_list *first)
{
	t_pids_list	*node;
	t_pids_list	*new_node;

	new_node = safe_malloc(sizeof(t_pids_list), ALLOC_COMMAND);
	new_node->pid = pid;
	new_node->next = NULL;
	if (!first)
		return (new_node);
	node = first;
	while (node->next)
		node = node->next;
	node->next = new_node;
	return (first);
}
