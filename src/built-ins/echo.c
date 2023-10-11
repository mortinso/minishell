/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:21:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 15:29:23 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	echo(char **cmd_flags) //g_exit > 0 if there's an error somehow
{
	int		j;
	int		cmds;
	int		n_flag;

	j = 1;
	n_flag = 0;
	cmds = cmd_args(cmd_flags, 0);
	if (cmd_flags && echo_flag(cmd_flags[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	if (cmds == 1)
		return (printf("\n"));
	while (cmd_flags && j < arr_size(cmd_flags))
	{
		printf("%s", cmd_flags[j++]);
		if (cmd_flags && j != arr_size(cmd_flags))
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	g_exit = 0;
	return (0);
}
