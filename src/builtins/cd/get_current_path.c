/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:39:03 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/14 19:07:35 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*no_pwd(void)
{
	char	buffer[PATH_MAX];
	char	*temp;

	getcwd(buffer, PATH_MAX);
	temp = safe_strdup(buffer, ALLOC_COMMAND);
	return (temp);
}

char	*get_current_path(t_minishell *minishell)
{
	char	*current_path;
	char	*temp;
	char	*res;
	int		line;

	line = get_env_var(minishell, "PWD", 3);
	if (line == -1)
		return (no_pwd());
	current_path = safe_strdup(minishell->env[line], ALLOC_COMMAND);
	if (!current_path)
		return (NULL);
	temp = current_path;
	while (*temp && *temp != '=')
		temp++;
	if (*temp == '=')
		temp++;
	res = safe_strdup(temp, ALLOC_COMMAND);
	return (res);
}
