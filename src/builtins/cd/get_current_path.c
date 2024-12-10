/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:39:03 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 12:51:22 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*no_pwd(void)
{
	char	buffer[PATH_MAX];
	char	*temp;

	getcwd(buffer, PATH_MAX);
	temp = ft_strdup(buffer);
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
	current_path = ft_strdup(minishell->env[line]);
	if (!current_path)
		return (NULL);
	temp = current_path;
	while (*temp && *temp != '=')
		temp++;
	if (*temp == '=')
		temp++;
	res = ft_strdup(temp);
	free(current_path);
	return (res);
}
