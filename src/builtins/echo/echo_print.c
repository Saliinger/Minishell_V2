/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukan <anoukan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:50:14 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/17 03:23:16 by anoukan          ###   ########.fr       */
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
		error += print_line(arg[i]);
		if (arg[i + 1] && ft_strlen(arg[i + 1]) > 0)
			printf(" ");
		i++;
	}
	if (eof == true)
		printf("\n");
	if (error > 0)
		return (1);
	return (0);
}
