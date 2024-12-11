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

int	ft_pwd(t_minishell *minishell)
{
	int		line;
	char	*pwd;
	char	*temp;

	line = get_env_var(minishell, "PWD", 3);
	if (line == -1)
	{
		printerr("The PWD is not set\n");
		return (1);
	}
	pwd = ft_strdup(minishell->env[line]);
	temp = pwd;
	while (*pwd != '=')
		pwd++;
	pwd++;
	printf("%s\n", pwd);
	free(temp);
	exit(0);
}
