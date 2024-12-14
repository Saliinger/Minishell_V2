/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:22 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/29 21:50:38 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// use of getcwd si pas de pwd

int	ft_pwd(t_minishell *minishell)
{
	int		line;
	char	*pwd;
	char    buffer[PATH_MAX + 1];

	line = get_env_var(minishell, "PWD", 3);
	if (line == -1)
	{
		getcwd(buffer, PATH_MAX);
		pwd = safe_strdup(buffer, ALLOC_COMMAND);
	}
	else
	{
		pwd = safe_strdup(minishell->env[line], ALLOC_COMMAND);
		while (*pwd != '=')
			pwd++;
		pwd++;
	}
	printf("%s\n", pwd);
	exit(0);
}
