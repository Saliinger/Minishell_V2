/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:55:45 by ekrebs            #+#    #+#             */
/*   Updated: 2024/11/30 00:25:52 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


// static int free_pipes(t_infos *i, int cmd_count)
// {
// 	int err;
// 	int j;

// 	err = 0;
// 	j = 0;
// 	if (!i->pipes)
// 		return (EXIT_SUCCESS);
// 	while (j < cmd_count - 1)
// 	{
// 		err += ft_close(&i->pipes[j][0]);
// 		err += ft_close( &i->pipes[j][1]);
// 		if (err)
// 			return (printerr("%s: %d: err closing in free_t_infos\n", __FILE__, __LINE__), ERR_PRIM);
// 		free(i->pipes[j]);
// 		j++;
// 	}
// 	free(i->pipes);
// 	return (EXIT_SUCCESS);
// }

/**
 * 
 * brief : frees the struct's data fields
 * 
 * 
 */
void	free_t_infos(t_infos *i)
{
	free_pids(&i->pids_llist);
	ft_close_pipes(i->cmd_count - 1, &i->pipes);
	//free_pipes(i, i->cmd_count);
}