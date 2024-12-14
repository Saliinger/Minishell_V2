/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:19:12 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:19:31 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	modify_value(t_export_list **lst, char *name, char *value)
{
	t_export_list	*tmp;

	tmp = find_export_node(name, lst);
	if (tmp)
		tmp->value = safe_strdup(value, ALLOC_MINISHELL);
	else
		return (1);
	return (0);
}
