/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:18:10 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 13:33:33 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by anoukan on 12/6/24.
//

#include "../../include/minishell.h"

int	delete_export_node(t_export_list **lst, char *name)
{
	t_export_list	*to_delete;
	t_export_list	*current;

	to_delete = find_export_node(name, lst);
	if (!to_delete)
		return (0);
	current = *lst;
	if (to_delete == current)
		*lst = (*lst)->next;
	while (current && current->next != to_delete)
		current = current->next;
	if (current && current->next == to_delete)
		current->next = current->next->next;
	else
		return (1);
	return (0);
}
