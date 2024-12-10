/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:13 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:20:47 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// need to print the env var

void	ft_expand(t_command_exec *command, t_minishell *minishell)
{
	int		i;
	char	*temp;
	int		temp_len;
	int		line;

	i = 0;
	while (command->cmd_args[i])
	{
		temp = ft_strdup(command->cmd_args[i] + 1);
		temp_len = ft_strlen(temp);
		line = get_env_var(minishell, temp, temp_len);
		if (line == -1)
			fprintf(stderr, "var doesn't exist");
		else
		{
			printf("%s", minishell->env[line] + temp_len + 1);
			if (command->cmd_args[i + 1])
				printf(" ");
		}
		free(temp);
		i++;
	}
	printf("\n");
	exit(0);
}
