/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:23:53 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 20:20:00 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*up_shlvl(char *str)
{
	char	*res;
	char	*value;
	int		shlvl;

	while (*str != '=')
		str++;
	str++;
	shlvl = ft_atoi(str);
	shlvl++;
	value = ft_itoa_safe(shlvl, ALLOC_MINISHELL);
	res = ft_strjoin_safe("SHLVL=", value, ALLOC_MINISHELL);
	return (res);
}

char	**get_env(char **env)
{
	int		i;
	char	**res;
	int		nbr_lines;

	i = 0;
	nbr_lines = nbr_of_line(env);
	if (!env)
		return (NULL);
	res = (char **)safe_malloc(sizeof(char *) * (nbr_lines + 1),
			ALLOC_MINISHELL);
	if (!res)
		return (NULL);
	while (i < nbr_lines)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			res[i] = up_shlvl(env[i]);
		else
			res[i] = safe_strdup(env[i], ALLOC_MINISHELL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_print(char **s, int i)
{
	if (!s)
	{
		fprintf(stderr, "Error: NULL pointer passed to ft_print.\n");
		return ;
	}
	printf("this is the args \n");
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

void	ft_print_redir(t_redir *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("node %d: %s\n", i, list->redir);
		i++;
		list = list->next;
	}
}
