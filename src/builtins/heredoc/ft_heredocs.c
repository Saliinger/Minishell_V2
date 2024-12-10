/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:54:19 by anoukan           #+#    #+#             */
/*   Updated: 2024/11/29 01:38:39 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	check_key(t_command *command, char *line)
{
	if (ft_strncmp(line, command->arg[1], ft_strlen(command->arg[1])) == 0
		&& ft_strlen(line) == ft_strlen(command->arg[1]))
		return (true);
	return (false);
}

static char	**dup_current_hd(t_minishell *minishell, char *new_line)
{
	char	**new_hd;
	int		i;

	i = 0;
	while (minishell->hd[i])
		i++;
	new_hd = (char **)malloc(sizeof(char *) * i + 1);
	if (!new_hd)
		return (NULL);
	i = 0;
	while (minishell->hd[i])
	{
		new_hd[i] = ft_strdup(minishell->hd[i]);
		i++;
	}
	new_hd[i] = ft_strdup(new_line);
	i++;
	new_hd[i] = NULL;
	return (new_hd);
}

static void	free_hd(char **hd)
{
	int	i;

	i = 0;
	while (hd[i])
	{
		free(hd[i]);
		i++;
	}
	free(hd);
}

static void	add_to_hd(t_minishell *minishell, char *hd)
{
	char	**new_hd;

	new_hd = dup_current_hd(minishell, hd);
	if (!new_hd)
		return ;
	if (minishell->hd)
		free_hd(minishell->hd);
	minishell->hd = new_hd;
}

int	ft_heredoc(t_command *command, t_minishell *minishell)
{
	int		flag;
	char	*line;
	char	*hd;

	flag = 1;
	hd = (char *)malloc(sizeof(char));
	hd[0] = '\0';
	while (flag)
	{
		line = readline(">");
		if (!line)
		{
			free(line);
			continue ;
		}
		else
		{
			if (check_key(command, line) == true)
				flag = 0;
			else
				hd = ft_strjoin_frees1(hd, line);
		}
	}
	add_to_hd(minishell, hd);
	return (0);
}

// add error for hd line 66