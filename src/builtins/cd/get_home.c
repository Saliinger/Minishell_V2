/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:37:23 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:07:37 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_home(t_minishell **minishell)
{
	t_export_list	*home;
	char			*line;

	home = find_export_node("HOME", (*minishell)->exportList);
	if (home)
	{
		line = safe_strdup(home->value, ALLOC_COMMAND);
		return (line);
	}
	return (NULL);
}
