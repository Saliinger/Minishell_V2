/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:45:03 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/10 17:31:25 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	ft_free(void **add)
{
	if (!add || !*add)
		return ;
	free(*add);
	*add = NULL;
	return ;
}

/**
 * in : t_redir **r, which is &rd;
 * brief : frees t_redir *rd and sets it to NULL;
 *
 */
void	ft_free_t_redir(t_redir **r)
{
	t_redir	*tmp;
	t_redir	*rd;

	if (!r || !*r)
		return ;
	rd = *r;
	while (rd)
	{
		tmp = rd->next;
		ft_free((void **)&rd->redir);
		ft_free((void **)&rd);
		rd = tmp;
	}
	*r = NULL;
}
