/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:37:23 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 12:51:24 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_home(t_minishell *minishell)
{
	t_export_list	*home;
	char			*line;

	home = find_export_node("HOME", minishell->exportList);
	if (home)
	{
		line = ft_strdup(home->value);
		return (line);
	}
	return (NULL);
}
