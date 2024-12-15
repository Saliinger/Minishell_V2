/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:34:56 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/15 20:39:58 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*display_prompt(char *prompt, t_minishell *minishell)
{
	char			*pwd;
	char			*name;
	char			*res;
	t_export_list	*node;


	if (prompt)
		free(prompt);
	node = find_export_node("USER", minishell->export_list);
	name = node->value;
	pwd = minishell->pwd;
	res = ft_strjoin(BLUE, name);
	res = ft_strjoin_frees1(res, "@");
	res = ft_strjoin_frees1(res, pwd);
	res = ft_strjoin_frees1(res, "$ ");
	res = ft_strjoin_frees1(res, RESET);
	return (res);
}
