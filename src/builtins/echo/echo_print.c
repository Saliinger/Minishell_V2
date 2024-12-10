/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:50:14 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/10 18:22:06 by anoukan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	print_line(char *line)
{
	size_t	len;

	len = printf("%s", line);
	if (len != ft_strlen(line))
		return (1);
	return (0);
}

int	echo_print(char **arg, bool eof, int i)
{
	int	error;

	error = 0;
	while (arg[i])
	{
		error = print_line(arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (eof == true)
		printf("\n");
	if (error)
		return (1);
	return (0);
}
