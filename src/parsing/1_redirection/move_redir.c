/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:50:21 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 12:52:44 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	add_node(t_enum_redir type, char *str, t_redir **head)
{
	t_redir	*new;
	t_redir	*temp;

	new = (t_redir *)safe_malloc(sizeof(t_redir), ALLOC_COMMAND);
	if (!new)
		return ;
	new->redir = safe_strdup(str, ALLOC_COMMAND);
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static t_enum_redir	get_redir_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (R_APPEND);
	else if (!ft_strncmp(str, ">", 1))
		return (R_OUTPUT);
	else if (!ft_strncmp(str, "<<", 2))
		return (R_HEREDOC);
	else if (!ft_strncmp(str, "<", 1))
		return (R_INPUT);
	return (R_INVALID);
}

t_redir	*extract_redir(char **in)
{
	int				i;
	t_redir			*redir_list;
	t_enum_redir	type;

	if (!in)
		return (NULL);
	redir_list = NULL;
	i = 0;
	while (in[i])
	{
		type = get_redir_type(in[i]);
		if (type != R_INVALID)
		{
			if (in[i + 1])
				add_node(type, in[i + 1], &redir_list);
		}
		i++;
	}
	return (redir_list);
}
