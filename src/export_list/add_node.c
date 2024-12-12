/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:18:20 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/06 23:18:25 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_node_export(t_export_list **list, char *name, char *value)
{
	t_export_list	*new;
	t_export_list	*tmp;

	new = (t_export_list *)safe_malloc(sizeof(t_export_list), ALLOC_MINISHELL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (list && new)
	{
		if (!*list)
			*list = new;
		else
		{
			tmp = *list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (0);
}
