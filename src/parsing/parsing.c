/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:58:08 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:13:57 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// just add few step to the arg to:
// - split and create new line for every redirection
// - create the t_redir linked list
// - remove all the '<' || '>' and their key
// - expand all the env var in "" or out
// - remove all the exteranal quote '' || ""

// to add check access to each redir->redir

t_command	*parsing(char *str, t_minishell *minishell)
{
	t_command	*current;
	t_command	*temp;

	str = tiny_expand(str, minishell);
	current = command_init(str);
	temp = current;
	while (temp)
	{
		temp->arg = relexer(temp->arg);
		temp->redirection = extract_redir(temp->arg);
		if (temp->arg)
			temp->clean_arg = clean_arg(temp->arg);
		if (temp->clean_arg)
		{
			temp->clean_arg = expand_in(temp->clean_arg, minishell);
			temp->clean_arg = remove_quote(temp->clean_arg);
		}
		temp = temp->subcommand;
	}
	return (current);
}
