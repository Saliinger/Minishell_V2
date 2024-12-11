/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:18:10 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:18:14 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by anoukan on 12/6/24.
//

#include "../../include/minishell.h"

int	delete_export_node(t_export_list **lst, char *name)
{
	t_export_list	*tmp;

	tmp = find_export_node(name, lst);
	while ((*lst)->next != tmp)
		*lst = (*lst)->next;
	if ((*lst)->next == tmp)
	{
		(*lst)->next = (*lst)->next->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	else
		return (1);
	return (0);
}
