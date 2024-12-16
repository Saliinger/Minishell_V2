/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:50:21 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 22:52:18 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*tiny_remove_quote(char *arg)
{
	int		i;
	char	*res;
	int		status;

	i = 0;
	status = 0;
	res = safe_strdup("", ALLOC_COMMAND);
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && status == 0)
			status = in_quote(status, arg[i]);
		else if ((arg[i] == '\'' && status == -1) || (arg[i] == '\"'
				&& status == 1))
			status = in_quote(status, arg[i]);
		else
			res = add_char(res, arg[i]);
		i++;
	}
	return (res);
}

// create the linked list containing all the redir for one command

static void	add_node(t_enum_redir type, char *str, t_redir **head)
{
	t_redir	*new;
	t_redir	*temp;

	new = (t_redir *)safe_malloc(sizeof(t_redir), ALLOC_COMMAND);
	if (!new)
		return ;
	new->redir = tiny_remove_quote(str);
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
