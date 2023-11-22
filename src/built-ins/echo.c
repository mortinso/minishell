/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:21:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/01 17:44:52 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//check if there is an echo flag
//Returns 1 if yes, 0 if no
int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (1);
	return (0);
}

void	echo_print(char **cmd_args, int pos)
{
	int	i;

	while (cmd_args && pos < arr_size(cmd_args))
	{
		i = 0;
		while (i < (int)ft_strlen(cmd_args[pos]) && cmd_args[pos][i])
		{
			if (cmd_args[pos][i])
				printf("%c", cmd_args[pos][i++]);
		}
		pos++;
		if (cmd_args && pos != arr_size(cmd_args))
			printf(" ");
	}
}

int	ft_echo(char **cmd_args)
{
	int		j;
	int		cmds;
	int		n_flag;

	j = 1;
	n_flag = 0;
	g_exit = 0;
	cmds = arr_size(cmd_args);
	if (cmd_args[1] && echo_flag(cmd_args[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	echo_print(cmd_args, j);
	if (cmds == 1)
		return (printf("\n"));
	if (!n_flag)
		printf("\n");
	return (0);
}
