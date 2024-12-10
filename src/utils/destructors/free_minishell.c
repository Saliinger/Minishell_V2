/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:35:20 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 17:30:58 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_export_list(t_export_list **list)
{
	t_export_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->name);
		free((*list)->value);
		free((*list));
		*list = temp;
	}
	free(list);
	list = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->pwd)
		free(minishell->pwd);
	if (minishell->old_pwd)
		free(minishell->old_pwd);
	if (minishell->env)
		ft_free_tab(minishell->env);
	if (minishell->paths)
		ft_free_tab(minishell->paths);
	if (minishell->hidden_env)
		ft_free_tab(minishell->hidden_env);
	if (minishell->hidden_env)
		ft_free_tab(minishell->hidden_env);
	if (minishell->exportList)
		free_export_list(minishell->exportList);
	free(minishell);
}

//	if (minishell->hd)
//		ft_free_tab(minishell->hd);