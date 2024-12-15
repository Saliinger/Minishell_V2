/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:36:32 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/15 17:37:09 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <time.h>

void close_fd(t_safe_fd **head)
{
	t_safe_fd *current;

	current = *head;
	while (current)
	{
		close(current->fd);
		current = current->next;
	}
}

void add_safe_fd(int fd, enum e_fd type)
{
	static t_safe_fd *head = NULL;
	t_safe_fd *block;
	t_safe_fd *temp;

	if (head && type == CLOSE_FD)
	{
		close_fd(&head);
		return;
	}
	if (type == OPEN_FD)
	{
		block = (t_safe_fd *)safe_malloc(sizeof(t_safe_fd *), ALLOC_COMMAND);
		block->fd = fd;
		block->next = NULL;
		if (!head)
			head = block;
		else
		{
			temp = head;
			while (temp->next)
				temp = temp->next;
			temp->next = block;
		}
	}

}
