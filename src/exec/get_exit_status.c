/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:48:52 by ekrebs            #+#    #+#             */
/*   Updated: 2024/12/16 20:49:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_exit_status(t_minishell *m, t_pids_list *pids)
{
	int	status;

	while (pids)
	{
		if (waitpid(pids->pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				m->exit_status[0] = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				m->exit_status[0] = 128 + WTERMSIG(status);
		}
		pids = pids->next;
	}
}
