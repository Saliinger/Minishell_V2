/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:02:35 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 18:50:51 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// remove external quote
char	*extend_remove_quote(char *s)
{
	int		j;
	char	*res;
	int		status;

	j = 0;
	status = 0;
	res = safe_strdup("", ALLOC_COMMAND);
	while (s[j])
	{
		if ((s[j] == '\'' || s[j] == '\"') && status == 0)
			status = in_quote(status, s[j]);
		else if ((s[j] == '\'' && status == -1) || (s[j] == '\"'
				&& status == 1))
			status = in_quote(status, s[j]);
		else
			res = add_char(res, s[j]);
		j++;
	}
	return (res);
}

char	**remove_quote(char **arg)
{
	int		i;
	char	**res;

	i = 0;
	res = (char **)safe_malloc(sizeof(char *) * (nbr_of_line(arg) + 1),
			ALLOC_COMMAND);
	while (arg[i])
	{
		res[i] = extend_remove_quote(arg[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
